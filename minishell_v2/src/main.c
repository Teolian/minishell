/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:31:09 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 19:46:02 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_line(char *line, t_shell *shell);
static void	shell_loop(t_shell *shell);
static int	run_non_interactive(int argc, char **argv, t_shell *shell);
static void	run_piped_mode(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	if (argc > 1 && ft_strncmp(argv[1], "-c", 3) == 0)
		return (run_non_interactive(argc, argv, &shell));
	else if (!isatty(STDIN_FILENO))
		run_piped_mode(&shell);
	else
		shell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}

static void	run_piped_mode(t_shell *shell)
{
	char	*line;

	setup_signals(CHILD_EXEC);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		execute_line(line, shell);
		free(line);
	}
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_signals(PARENT_PROMPT);
		line = readline(PROMPT);
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("exit", 2);
			break ;
		}
		if (*line)
			add_history(line);
		execute_line(line, shell);
		free(line);
	}
}

static void	execute_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_token	*tokens_head;
	t_cmd	*cmd;

	if (line && *line)
	{
		tokens = lexer(line, shell);
		if (tokens == NULL)
			return ;
		tokens_head = tokens;
		cmd = parse_command(&tokens, shell);
		if (cmd)
		{
			execute_ast(cmd, shell);
			free_ast(cmd);
		}
		free_tokens(tokens_head);
	}
}

static int	run_non_interactive(int argc, char **argv, t_shell *shell)
{
	char	*cmd_str;

	if (argc < 3)
	{
		ft_putstr_fd("minishell: -c: option requires an argument\n", 2);
		return (2);
	}
	cmd_str = ft_strdup(argv[2]);
	setup_signals(CHILD_EXEC);
	execute_line(cmd_str, shell);
	free(cmd_str);
	free_shell(shell);
	return (shell->exit_status);
}
