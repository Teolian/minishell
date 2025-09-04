/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:19 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:56:40 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	perform_exit(char **args, t_shell *shell)
{
	int	exit_code;

	if (!args[1])
	{
		free_shell(shell);
		exit(shell->exit_status);
	}
	if (!is_numeric(args[1]))
	{
		free_shell(shell);
		handle_numeric_arg_required(args[1]);
	}
	exit_code = ft_atoi(args[1]);
	free_shell(shell);
	exit(exit_code % 256);
}

void	ft_exit(char **args, t_shell *shell)
{
	if (args[1] && is_numeric(args[1]) && args[2])
	{
		handle_too_many_args(shell);
		return ;
	}
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	perform_exit(args, shell);
}
