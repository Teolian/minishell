#!/bin/bash

# Простой тестер для minishell - положите в папку с minishell
# Использование: ./test_minishell.sh

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

MINISHELL="./minishell"
PASSED=0
FAILED=0
TOTAL=0

# Проверка наличия minishell
check_minishell() {
    if [ ! -f "Makefile" ]; then
        echo -e "${RED}❌ Makefile не найден в текущей папке${NC}"
        exit 1
    fi
    
    echo -e "${BLUE}🔨 Компилируем minishell...${NC}"
    make > /dev/null 2>&1
    
    if [ ! -f "$MINISHELL" ]; then
        echo -e "${RED}❌ minishell не скомпилирован${NC}"
        exit 1
    fi
    
    if [ ! -x "$MINISHELL" ]; then
        chmod +x "$MINISHELL"
    fi
    
    echo -e "${GREEN}✅ minishell готов к тестированию${NC}"
}

# Функция для выполнения теста
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_exit_code="${3:-0}"
    
    echo -n -e "${BLUE}🔍 $test_name:${NC} "
    
    # Создаем временный файл для команды
    echo "$command" > /tmp/minishell_cmd
    echo "exit" >> /tmp/minishell_cmd
    
    # Запускаем с timeout
    timeout 5s $MINISHELL < /tmp/minishell_cmd > /tmp/minishell_out 2>/tmp/minishell_err
    local exit_code=$?
    
    TOTAL=$((TOTAL + 1))
    
    if [ $exit_code -eq 124 ]; then
        echo -e "${YELLOW}⏰ TIMEOUT${NC}"
        FAILED=$((FAILED + 1))
    elif [ $exit_code -eq $expected_exit_code ]; then
        echo -e "${GREEN}✅ PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}❌ FAIL (exit: $exit_code, expected: $expected_exit_code)${NC}"
        FAILED=$((FAILED + 1))
        # Показать первые строки ошибки
        head -2 /tmp/minishell_err 2>/dev/null | sed 's/^/   /'
    fi
    
    rm -f /tmp/minishell_cmd /tmp/minishell_out /tmp/minishell_err
}

# Функция для сравнения вывода с bash
compare_with_bash() {
    local test_name="$1"
    local command="$2"
    
    echo -n -e "${BLUE}🔍 $test_name:${NC} "
    
    # Выполняем в bash
    echo "$command" | bash > /tmp/bash_out 2>/tmp/bash_err
    local bash_exit=$?
    
    # Выполняем в minishell
    echo -e "$command\nexit" | timeout 5s $MINISHELL > /tmp/minishell_out 2>/tmp/minishell_err
    local mini_exit=$?
    
    TOTAL=$((TOTAL + 1))
    
    if [ $mini_exit -eq 124 ]; then
        echo -e "${YELLOW}⏰ TIMEOUT${NC}"
        FAILED=$((FAILED + 1))
    elif diff /tmp/bash_out /tmp/minishell_out > /dev/null 2>&1; then
        echo -e "${GREEN}✅ PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}❌ FAIL (output differs)${NC}"
        FAILED=$((FAILED + 1))
        echo -e "   ${YELLOW}Expected:${NC}"
        head -2 /tmp/bash_out 2>/dev/null | sed 's/^/   /'
        echo -e "   ${YELLOW}Got:${NC}"
        head -2 /tmp/minishell_out 2>/dev/null | sed 's/^/   /'
    fi
    
    rm -f /tmp/bash_out /tmp/bash_err /tmp/minishell_out /tmp/minishell_err
}

echo -e "${BLUE}🧪 Тестер minishell${NC}"
echo "=========================="

check_minishell

echo
echo -e "${BLUE}📋 Базовые команды:${NC}"
run_test "Пустая команда" ""
compare_with_bash "echo hello" "echo hello"
compare_with_bash "echo с флагом -n" "echo -n hello"
compare_with_bash "pwd" "pwd"
run_test "env (первые 3 строки)" "env | head -3"

echo
echo -e "${BLUE}📋 Встроенные команды:${NC}"
run_test "cd в /tmp" "cd /tmp && pwd"
run_test "cd домой" "cd && pwd"
run_test "export переменной" "export TEST=hello && echo \$TEST"
run_test "export без значения" "export TEST2"
run_test "unset переменной" "export TEST3=value && unset TEST3 && echo \$TEST3"
compare_with_bash "export без аргументов" "export | head -3"

echo
echo -e "${BLUE}📋 Переменные окружения:${NC}"
compare_with_bash "Переменная PATH" "echo \$PATH | cut -d: -f1"
compare_with_bash "Переменная HOME" "echo \$HOME"
run_test "Exit status" "echo \$?"
run_test "Несуществующая переменная" "echo \$NONEXISTENT"

echo
echo -e "${BLUE}📋 Перенаправления:${NC}"
run_test "Redirect out" "echo test > /tmp/test_mini && cat /tmp/test_mini"
run_test "Redirect append" "echo test1 > /tmp/test_mini2 && echo test2 >> /tmp/test_mini2 && cat /tmp/test_mini2"
run_test "Redirect in" "echo testinput > /tmp/test_input && cat < /tmp/test_input"

echo
echo -e "${BLUE}📋 Heredoc:${NC}"
run_test "Простой heredoc" "cat << EOF
hello
world
EOF"

echo
echo -e "${BLUE}📋 Pipes:${NC}"
run_test "Простой pipe" "echo hello | cat"
run_test "Pipe с wc" "echo -e 'line1\nline2\nline3' | wc -l"
run_test "Множественные pipes" "echo hello | cat | cat | wc -c"
run_test "ls через pipe" "ls -la | head -2 | wc -l"

echo
echo -e "${BLUE}📋 Комбинированные команды:${NC}"
run_test "Команды через ;" "echo first; echo second"
run_test "Pipe с redirect" "echo test | cat > /tmp/pipe_test && cat /tmp/pipe_test"
run_test "Сложная комбинация" "echo start && echo middle | cat && echo end"

echo
echo -e "${BLUE}📋 Обработка ошибок:${NC}"
run_test "Несуществующая команда" "nonexistentcommand" 127
run_test "Команда без прав" "cd /root" 1
run_test "Неправильный синтаксис" "echo |" 2

echo
echo -e "${BLUE}📋 Расширенные тесты:${NC}"
run_test "Много аргументов" "echo a b c d e f g h i j"
run_test "Кавычки одинарные" "echo 'hello world'"
run_test "Кавычки двойные" "echo \"hello world\""
run_test "Смешанные кавычки" "echo 'hello \"world\"'"

# Очистка временных файлов
rm -f /tmp/test_mini /tmp/test_mini2 /tmp/test_input /tmp/pipe_test

echo
echo "=========================="
echo -e "${BLUE}📊 Результаты:${NC}"
echo -e "${GREEN}✅ Пройдено: $PASSED${NC}"
echo -e "${RED}❌ Провалено: $FAILED${NC}"
echo -e "${BLUE}📝 Всего тестов: $TOTAL${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 Все тесты пройдены!${NC}"
    exit 0
else
    echo -e "${YELLOW}⚠️  Есть проблемы для исправления${NC}"
    exit 1
fi