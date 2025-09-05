/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:08:06 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:54:38 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	return (0);
}

int	is_parent_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	return (0);
}

int	dispatch_builtin(t_exec_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		shell->exit_status = ft_echo(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		shell->exit_status = ft_cd(cmd->argv, shell);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		shell->exit_status = ft_pwd();
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		shell->exit_status = ft_env(shell);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		ft_exit(cmd->argv, shell);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		shell->exit_status = ft_export(cmd->argv, shell);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		shell->exit_status = ft_unset(cmd->argv, shell);
	else
		return (0);
	return (1);
}
