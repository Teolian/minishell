#!/bin/bash

# Простой тестер для отладки на macOS

echo "=== Отладка minishell на macOS ==="

echo "1. Проверяем, что minishell запускается:"
echo 'echo "Hello from minishell"
exit' | ./minishell

echo -e "\n2. Проверяем heredoc проблему:"
echo 'cat << EOF
test line
EOF
exit' | ./minishell

echo -e "\n3. Проверяем обычные команды:"
echo 'pwd
echo hello
exit' | ./minishell

echo -e "\n4. Тест с файлом:"
echo 'cat << EOF
line1
line2  
EOF' > /tmp/test_heredoc_input
echo 'exit' >> /tmp/test_heredoc_input

echo "Содержимое тестового файла:"
cat /tmp/test_heredoc_input
echo -e "\nРезультат выполнения:"
./minishell < /tmp/test_heredoc_input

rm -f /tmp/test_heredoc_input