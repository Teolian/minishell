/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:31:09 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:58:39 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_line(char *line, t_shell *shell);
static void	shell_loop(t_shell *shell);
static int	run_non_interactive(int argc, char **argv, t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "-c", 3) == 0)
			return (run_non_interactive(argc, argv, &shell));
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (127);
		}
	}
	else
		shell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}

static void	execute_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_token	*tokens_head;
	t_cmd	*cmd;

	if (line && *line)
	{
		add_history(line);
		tokens = lexer(line, shell);
		if (tokens == NULL)
		{
			free(line);
			return ;
		}
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
		execute_line(line, shell);
		free(line);
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
