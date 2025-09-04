#!/bin/bash

echo "Testing heredoc manually:"
echo

echo "1. Testing cat with heredoc in bash:"
cat << EOF
hello
world
EOF

echo
echo "2. Now testing with your minishell:"
echo 'cat << EOF
hello  
world
EOF' | ./minishell

echo
echo "3. Expected: cat should read 'hello\\nworld' from stdin and output it"
echo "   Your minishell probably tries to execute 'hello' and 'world' as commands"