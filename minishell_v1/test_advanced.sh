#!/bin/bash

# Исправленный продвинутый тестер для minishell
# Положите в папку с minishell и запустите: ./test_advanced_fixed.sh

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
NC='\033[0m'

MINISHELL="./minishell"
MINISHELL_PATH=$(pwd)
TEST_DIR="/tmp/minishell_tests_$$"
PASSED=0
FAILED=0

# Подготовка
setup() {
    if [ ! -f "Makefile" ]; then
        echo -e "${RED}❌ Запустите в папке с minishell${NC}"
        exit 1
    fi
    
    echo -e "${BLUE}🔨 Компилируем...${NC}"
    make re > /dev/null 2>&1
    
    if [ ! -x "$MINISHELL" ]; then
        echo -e "${RED}❌ Не удалось скомпилировать minishell${NC}"
        exit 1
    fi
    
    mkdir -p "$TEST_DIR"
}

# Тест с полным контролем
test_command() {
    local name="$1"
    local cmd="$2"
    local expected_exit="${3:-0}"
    local timeout_sec="${4:-3}"
    
    echo -n -e "${BLUE}🔍 $name:${NC} "
    
    # Подготавливаем команды в TEST_DIR, но запускаем minishell из MINISHELL_PATH
    echo -e "$cmd\nexit" > "$TEST_DIR/cmd_input"
    
    # Выполняем с timeout, указывая полный путь к minishell
    cd "$TEST_DIR"
    timeout ${timeout_sec}s "$MINISHELL_PATH/$MINISHELL" < cmd_input > minishell_out 2>minishell_err
    local actual_exit=$?
    cd "$MINISHELL_PATH"
    
    if [ $actual_exit -eq 124 ]; then
        echo -e "${YELLOW}⏰ TIMEOUT${NC}"
        FAILED=$((FAILED + 1))
    elif [ $actual_exit -eq $expected_exit ]; then
        echo -e "${GREEN}✅ PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}❌ FAIL (exit: $actual_exit ≠ $expected_exit)${NC}"
        FAILED=$((FAILED + 1))
        head -2 "$TEST_DIR/minishell_err" | sed 's/^/   /'
    fi
    
    rm -f "$TEST_DIR/cmd_input" "$TEST_DIR/minishell_out" "$TEST_DIR/minishell_err"
}

# Сравнение с bash
test_vs_bash() {
    local name="$1"
    local cmd="$2"
    
    echo -n -e "${BLUE}🔍 $name:${NC} "
    
    # Выполняем в bash
    cd "$TEST_DIR"
    echo "$cmd" | bash > bash_out 2>bash_err
    
    # Выполняем в minishell
    echo -e "$cmd\nexit" | timeout 3s "$MINISHELL_PATH/$MINISHELL" > mini_out 2>mini_err
    local mini_exit=$?
    cd "$MINISHELL_PATH"
    
    if [ $mini_exit -eq 124 ]; then
        echo -e "${YELLOW}⏰ TIMEOUT${NC}"
        FAILED=$((FAILED + 1))
    elif diff "$TEST_DIR/bash_out" "$TEST_DIR/mini_out" > /dev/null 2>&1; then
        echo -e "${GREEN}✅ PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}❌ FAIL${NC}"
        FAILED=$((FAILED + 1))
        echo -e "   ${YELLOW}Bash:${NC} $(head -1 "$TEST_DIR/bash_out")"
        echo -e "   ${YELLOW}Mini:${NC} $(head -1 "$TEST_DIR/mini_out")"
    fi
    
    rm -f "$TEST_DIR/bash_out" "$TEST_DIR/bash_err" "$TEST_DIR/mini_out" "$TEST_DIR/mini_err"
}

echo -e "${PURPLE}🚀 Исправленный тестер minishell${NC}"
echo "===================================="

setup

echo -e "${BLUE}📋 Базовые встроенные команды${NC}"
test_vs_bash "echo простой" "echo hello"
test_vs_bash "echo -n" "echo -n hello"
test_vs_bash "echo множественные -n" "echo -nnn hello"
test_vs_bash "pwd" "pwd"

echo
echo -e "${BLUE}📋 Управление директориями${NC}"
test_command "cd /tmp" "cd /tmp && pwd"
test_command "cd домой" "cd ~ && pwd"
test_command "cd несуществующая" "cd /nonexistent" 1
test_command "cd слишком много аргументов" "cd /tmp /usr" 1

echo
echo -e "${BLUE}📋 Переменные окружения${NC}"
test_command "export новая" "export TESTVAR=hello && echo \$TESTVAR"
test_command "export перезапись" "export PATH=/test && echo \$PATH"
test_command "export без значения" "export EMPTYVAR && env | grep EMPTYVAR"
test_command "unset существующую" "export TESTVAR2=world && unset TESTVAR2 && echo \$TESTVAR2"
test_command "unset PATH" "unset PATH && echo \$PATH"

echo
echo -e "${BLUE}📋 Расширение переменных${NC}"
test_vs_bash "Простая переменная" 'export TEST=hello && echo $TEST'
test_vs_bash "Exit status" 'ls /nonexistent 2>/dev/null; echo $?'
test_vs_bash "Переменная в кавычках" 'export TEST=world && echo "hello $TEST"'
test_vs_bash "Переменная в одинарных кавычках" 'export TEST=world && echo '\''$TEST'\'''
test_command "Несуществующая переменная" 'echo $NONEXISTENT123'

echo
echo -e "${BLUE}📋 Перенаправления${NC}"
echo "test content" > "$TEST_DIR/test_file"
test_command "Redirect input" "cat < test_file"
test_command "Redirect output" "echo test123 > out_file && cat out_file"
test_command "Redirect append" "echo line1 > app_file && echo line2 >> app_file && cat app_file"
test_command "Redirect к несуществующему файлу" "cat < nonexistent" 1

echo
echo -e "${BLUE}📋 Heredoc${NC}"
test_command "Простой heredoc" 'cat << EOF
line1
line2
EOF'

echo
echo -e "${BLUE}📋 Конвейеры (pipes)${NC}"
test_vs_bash "Простой pipe" "echo hello | cat"
test_vs_bash "Pipe с wc" "echo -e 'hello\nworld' | wc -l"
test_vs_bash "Множественный pipe" "echo hello | cat | cat | wc -c"
test_command "Pipe с неверной командой" "echo hello | invalidcommand" 127

echo
echo -e "${BLUE}📋 Логические операторы${NC}"
test_command "Успешная && успешная" "echo first && echo second"
test_command "Успешная && неуспешная" "echo success && /bin/false" 1
test_command "Неуспешная && успешная" "/bin/false && echo success" 1
test_command "Неуспешная || успешная" "/bin/false || echo success"
test_command "Успешная || неуспешная" "echo success || /bin/false"

echo
echo -e "${BLUE}📋 Последовательность команд${NC}"
test_command "Команды через ;" "echo first; echo second"

echo
echo -e "${BLUE}📋 Обработка кавычек${NC}"
test_vs_bash "Двойные кавычки" 'echo "hello world"'
test_vs_bash "Одинарные кавычки" "echo 'hello world'"
test_vs_bash "Смешанные кавычки" 'echo "hello'\''world"'
test_vs_bash "Кавычки с переменными" 'export TEST=value && echo "test $TEST"'
test_vs_bash "Одинарные кавычки блокируют переменные" 'export TEST=value && echo '\''$TEST'\'''

echo
echo -e "${BLUE}📋 Обработка ошибок${NC}"
test_command "Несуществующая команда" "nonexistentcommand123" 127
test_command "Неправильный синтаксис |" "echo hello |" 2
test_command "Неправильный синтаксис >" "echo hello >" 2
test_command "Неправильный синтаксис <" "cat <" 2

echo
echo -e "${BLUE}📋 Exit команда${NC}"
test_command "exit 0" "exit 0" 0
test_command "exit 1" "exit 1" 1
test_command "exit 42" "exit 42" 42
test_command "exit с нечисловым аргументом" "exit abc" 2

# Очистка
rm -rf "$TEST_DIR"

echo
echo "===================================="
echo -e "${BLUE}📊 Итоговые результаты:${NC}"
echo -e "${GREEN}✅ Пройдено: $PASSED${NC}"
echo -e "${RED}❌ Провалено: $FAILED${NC}"

TOTAL=$((PASSED + FAILED))
if [ $TOTAL -gt 0 ]; then
    PERCENTAGE=$((PASSED * 100 / TOTAL))
    echo -e "${BLUE}📈 Процент успеха: $PERCENTAGE%${NC}"
fi

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 Поздравляем! Все тесты пройдены!${NC}"
else
    echo -e "${YELLOW}⚠️  Нужно исправить $FAILED тест(ов)${NC}"
fi

exit $FAILED