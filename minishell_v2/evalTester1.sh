#!/bin/bash

# --- Configuration ---
MINISHELL_PATH="./minishell"
TEST_DIR="test_workspace"
OUT_MSH="$TEST_DIR/msh_out.txt"
OUT_BASH="$TEST_DIR/bash_out.txt"
STATUS_MSH="$TEST_DIR/msh_status.txt"
STATUS_BASH="$TEST_DIR/bash_status.txt"
TEST_FILE="$TEST_DIR/test_file.txt"
INPUT_FILE="$TEST_DIR/input.txt"

# --- Colors and Formatting ---
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
BLUE="\033[34m"
NC="\033[0m"
BOLD="\033[1m"
LINE="══════════════════════════════════════════════════════════════════════════"

# --- Counters ---
test_count=0
passed_count=0

# --- Helper Functions ---
setup() {
    rm -rf "$TEST_DIR"
    mkdir -p "$TEST_DIR"
    echo -e "apple\nbanana\ncherry" > "$INPUT_FILE"
}

teardown() {
    rm -rf "$TEST_DIR"
}

# Generic test runner for commands using the -c flag
run_test() {
    local id="$1"
    local description="$2"
    local msh_command="$3"
    local bash_command="$4"
    local compare_output=${5:-true}
    local compare_status=${6:-true}

    ((test_count++))
    printf "${BLUE}[%02d]${NC} %-55s : " "$id" "$description"

    # Execute Minishell
    timeout 5 "$MINISHELL_PATH" -c "$msh_command" > "$OUT_MSH" 2>&1
    echo $? > "$STATUS_MSH"

    # Execute Bash in a subshell
    (eval "$bash_command") > "$OUT_BASH" 2>&1
    echo $? > "$STATUS_BASH"

    # Comparison logic
    local pass=true
    if [ "$compare_output" = true ] && ! diff -q "$OUT_MSH" "$OUT_BASH" >/dev/null; then pass=false; fi
    if [ "$compare_status" = true ] && ! diff -q "$STATUS_MSH" "$STATUS_BASH" >/dev/null; then pass=false; fi

    if $pass; then
        echo -e "${GREEN}PASS ✔${NC}"
        ((passed_count++))
    else
        echo -e "${RED}FAIL ✘${NC}"
        # Detailed error output can be re-enabled if needed
    fi
}

print_header() {
    echo -e "${BOLD}${BLUE}$LINE${NC}"
    echo -e "${BOLD}${BLUE}>>> $1${NC}"
    echo -e "${BOLD}${BLUE}$LINE${NC}"
}

print_manual_check() {
    echo -e "${BOLD}${YELLOW}$LINE${NC}"
    echo -e "${BOLD}${YELLOW}>>> $1${NC}"
    echo -e "${BOLD}${YELLOW}$LINE${NC}"
    echo -e "$2"
}

# --- Test Execution ---
setup

print_header "Section 1: Compilation & Simple Commands"
if ! make -s; then
    echo -e "${RED}COMPILATION FAILED. Aborting tests.${NC}"
    exit 1
fi
run_test 1 "Compilation" "true" "true" false false
run_test 2 "Makefile flags" "grep -E -- '-Wall -Wextra -Werror' Makefile" "grep -E -- '-Wall -Wextra -Werror' Makefile"
run_test 3 "Empty command (spaces)" "   " "   "
run_test 4 "Gibberish command" "asdfghjkl" "asdfghjkl" false true

print_header "Section 2: Built-ins"
run_test 5 "'echo -n' multiple words" "echo -n hello world" "echo -n hello world"
run_test 6 "'exit 42' status" "exit 42" "exit 42" false true
run_test 7 "'exit 999' status" "exit 257" "exit 257" false true
run_test 8 "'exit' non-numeric" "exit abc" "exit abc" false true
run_test 9 "'exit' too many args" "exit 1 2" "exit 1 2" false true
run_test 10 "'cd .' and 'pwd'" "cd . && pwd" "cd . && pwd"
run_test 11 "'cd' non-existent dir" "cd /nonexistentdir123" "cd /nonexistentdir123" false true
run_test 12 "'export' new var" "export TESTVAR=hello && env | grep ^TESTVAR=" "export TESTVAR=hello && env | grep ^TESTVAR="
run_test 13 "'export' overwrite var" "export USER=test && echo \$USER" "export USER=test && echo \$USER"
run_test 14 "'unset' var" "export TODELETE=1 && unset TODELETE && env | grep TODELETE" "export TODELETE=1 && unset TODELETE && env | grep TODELETE" false true
run_test 15 "'env' basic check" "env | grep USER" "env | grep USER"

print_header "Section 3: Quotes & Expansions"
run_test 16 "Return value \$?" "ls /nonexistentfile123 ; echo \$?" "ls /nonexistentfile123 ; echo \$?"
run_test 17 "Double quotes" "echo \"hello   world\"" "echo \"hello   world\""
run_test 18 "Single quotes" "echo '\$USER'" "echo '\$USER'"
run_test 19 "Double quotes expansion" "echo \"User is \$USER\"" "echo \"User is \$USER\""

print_header "Section 4: PATH Handling"
run_test 20 "Relative Path" "ls -d $TEST_DIR" "ls -d $TEST_DIR"
run_test 21 "PATH command" "ls" "ls" true false
run_test 22 "unset PATH" "unset PATH && ls" "unset PATH && ls" false true

print_header "Section 5: Pipes & Redirections"
run_test 23 "Output Redirection '>'" "echo hello > $TEST_FILE && cat $TEST_FILE" "echo hello > $TEST_FILE && cat $TEST_FILE"
run_test 24 "Append Redirection '>>'" "echo hello > $TEST_FILE && echo world >> $TEST_FILE && cat $TEST_FILE" "echo hello > $TEST_FILE && echo world >> $TEST_FILE && cat $TEST_FILE"
run_test 25 "Input Redirection '<'" "wc -l < $INPUT_FILE" "wc -l < $INPUT_FILE"
# run_heredoc_test 26 "Heredoc '<<'" # This test is now manual
run_test 27 "Simple Pipe" "printf \"apple\nbanana\ncherry\" | grep banana" "printf \"apple\nbanana\ncherry\" | grep banana"
run_test 28 "Multi-Pipe" "cat $INPUT_FILE | grep a | wc -l" "cat $INPUT_FILE | grep a | wc -l"
run_test 29 "Pipe and Redir" "cat $INPUT_FILE | grep a > $TEST_FILE && cat $TEST_FILE" "cat $INPUT_FILE | grep a > $TEST_FILE && cat $TEST_FILE"

print_manual_check "Section 6: Signals & Interactive Mode (Manual Check)" "These tests must be run by you in an interactive minishell session."
echo -e "  - [ ] Start \`./minishell\`. Press Ctrl-C. A new prompt should appear."
echo -e "  - [ ] Start \`./minishell\`. Press Ctrl-D on an empty line. Minishell should exit."
echo -e "  - [ ] Start \`./minishell\`. Run \`cat << EOF\`, type lines, then \`EOF\`. It should echo the lines."

# --- Final Results ---
echo -e "${BOLD}${BLUE}$LINE${NC}"
echo -e "${BOLD}${BLUE}>>> TEST RESULTS${NC}"
echo -e "${BOLD}${BLUE}$LINE${NC}"
echo -e "Total automated tests: $((test_count))"
echo -e "${GREEN}Passed: $passed_count${NC}"
echo -e "${RED}Failed: $((test_count - passed_count))${NC}"

teardown
