#!/bin/bash

echo "=== Отладка проблемы с stdin ==="

# Тест 1: Простая команда без heredoc
echo "1. Тест обычной команды:"
echo 'echo "normal command"' | ./minishell

echo -e "\n2. Тест с файлом:"
cat > /tmp/test_input << 'EOF'
echo "before heredoc"
cat << DELIMITER
data line 1
data line 2
DELIMITER
echo "after heredoc"
exit
EOF

echo "Содержимое файла:"
cat /tmp/test_input

echo -e "\nВыполнение:"
./minishell < /tmp/test_input

echo -e "\n3. Проверка - что происходит с обычным cat:"
cat > /tmp/regular_test << 'EOF' 
echo "testing regular command"
exit
EOF

echo "Обычная команда:"
./minishell < /tmp/regular_test

rm -f /tmp/test_input /tmp/regular_test