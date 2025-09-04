#!/bin/bash

# Исправленный тестер для macOS
# Использование: ./test_advanced_macos.sh

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

# Проверка наличия timeout (для macOS нужен gtimeout)
if command -v timeout >/dev/null 2>&1; then
    TIMEOUT_CMD="timeout"
elif command -v gtimeout >/dev/null 2>&1; then
    TIMEOUT_CMD="gtimeout"
else
    TIMEOUT_CMD=""
fi

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

# Тест с учетом macOS
test_command() {
    local name="$1"
    local cmd="$2"
    local expected_exit="${3:-0}"
    local timeout_sec="${4:-3}"
    
    echo -n -e "${BLUE}🔍 $name:${NC} "
    
    # Подготавливаем команды
    echo -e "$cmd\nexit" > "$TEST_DIR/cmd_input"
    
    # Выполняем с timeout если доступен
    cd "$TEST_DIR"
    if [ -n "$TIMEOUT_CMD" ]; then
        $TIMEOUT_CMD ${timeout_sec}s "$MINISHELL_PATH/$MINISHELL" < cmd_input > minishell_out 2>minishell_err
    else
        "$MINISHELL_PATH/$MINISHELL" < cmd_input > minishell_out 2>minishell_err
    fi
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

# Сравнение с bash с учетом macOS путей
test_vs_bash() {
    local name="$1"
    local cmd="$2"
    
    echo -n -e "${BLUE}🔍 $name:${NC} "
    
    # Выполняем в bash
    cd "$TEST_DIR"
    echo "$cmd" | bash > bash_out 2>bash_err
    
    # Выполняем в minishell
    if [ -n "$TIMEOUT_CMD" ]; then
        echo -e "$cmd\nexit" | $TIMEOUT_CMD 3s "$MINISHELL_PATH/$MINISHELL" > mini_out 2>mini_err
    else
        echo -e "$cmd\nexit" | "$MINISHELL_PATH/$MINISHELL" > mini_out 2>mini_err
    fi
    local mini_exit=$?
    cd "$MINISHELL_PATH"
    
    # Нормализуем пути для macOS (убираем /private)
    sed 's|/private/tmp|/tmp|g' mini_out > mini_out_norm 2>/dev/null || cp mini_out mini_out_norm
    
    if [ $mini_exit -eq 124 ]; then
        echo -e "${YELLOW}⏰ TIMEOUT${NC}"
        FAILED=$((FAILED + 1))
    elif diff "$TEST_DIR/bash_out" "$TEST_DIR/mini_out_norm" > /dev/null 2>&1; then
        echo -e "${GREEN}✅ PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}❌ FAIL${NC}"
        FAILED=$((FAILED + 1))
        echo -e "   ${YELLOW}Bash:${NC} $(head -1 "$TEST_DIR/bash_out")"
        echo -e "   ${YELLOW}Mini:${NC} $(head -1 "$TEST_DIR/mini_out_norm")"
    fi
    
    rm -f "$TEST_DIR/bash_out" "$TEST_DIR/bash_err" "$TEST_DIR/mini_out" "$TEST_DIR/mini_err" "$TEST_DIR/mini_out_norm"
}

echo -e "${PURPLE}🚀 macOS тестер minishell${NC}"
echo "===================================="

setup

echo -e "${BLUE}📋 Базовые встроенные команды${NC}"
test_vs_bash "echo простой" "echo hello"
test_vs_bash "echo -n" "echo -n hello"
test_vs_bash "pwd" "pwd"

echo
echo -e "${BLUE}📋 Логические операторы (исправлено для macOS)${NC}"
test_command "Успешная && успешная" "echo first && echo second"
test_command "Успешная && неуспешная" "echo success && false" 1
test_command "Неуспешная && успешная" "false && echo success" 1
test_command "Неуспешная || успешная" "false || echo success"
test_command "Успешная || неуспешная" "echo success || false"

echo
echo -e "${BLUE}📋 Heredoc${NC}"
test_command "Простой heredoc" 'cat << EOF
line1
line2
EOF'

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
    echo -e "${GREEN}🎉 Все тесты пройдены!${NC}"
else
    echo -e "${YELLOW}⚠️  Нужно исправить $FAILED тест(ов)${NC}"
fi

exit $FAILED