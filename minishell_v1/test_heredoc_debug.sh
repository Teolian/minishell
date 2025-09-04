#!/bin/bash

# Тест для отладки heredoc
echo "Тестируем heredoc..."

echo "=== Тест 1: Простой heredoc ==="
./minishell << 'TEST1'
cat << EOF
hello
world
EOF
exit
TEST1

echo -e "\n=== Тест 2: Heredoc с wc ==="
./minishell << 'TEST2'  
wc -l << EOF
line1
line2
line3
EOF
exit
TEST2

echo -e "\n=== Тест 3: Bash для сравнения ==="
bash << 'TEST3'
cat << EOF
hello
world
EOF
TEST3