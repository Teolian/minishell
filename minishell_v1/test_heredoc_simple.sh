#!/bin/bash

echo "=== Простой тест heredoc ==="

echo "Тестируем cat с heredoc:"
cat << EXPECTED > /tmp/expected_output
hello world
line two
EXPECTED

echo "Создаем входной файл для minishell:"
cat << INPUT > /tmp/minishell_input
cat << DELIMITER
hello world
line two
DELIMITER
exit
INPUT

echo "Содержимое входного файла:"
cat /tmp/minishell_input

echo -e "\nВыполняем в minishell:"
./minishell < /tmp/minishell_input > /tmp/minishell_output 2>&1

echo "Результат minishell:"
cat /tmp/minishell_output

echo -e "\nОжидаемый результат:"
cat /tmp/expected_output

echo -e "\nСравнение:"
if diff /tmp/expected_output /tmp/minishell_output > /dev/null 2>&1; then
    echo "✅ HEREDOC РАБОТАЕТ!"
else
    echo "❌ Heredoc не работает"
    echo "Различия:"
    diff /tmp/expected_output /tmp/minishell_output
fi

# Очистка
rm -f /tmp/expected_output /tmp/minishell_input /tmp/minishell_output