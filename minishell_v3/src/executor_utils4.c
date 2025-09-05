/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:42:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:56:59 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_parent_builtin(t_exec_cmd *ecmd, t_list *redir_list,
		t_shell *shell)
{
	int	fds[2];

	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
	if (apply_redirections(redir_list, shell))
		dispatch_builtin(ecmd, shell);
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
}

void	prepare_and_exec_command(t_exec_cmd *cmd, t_shell *shell)
{
	char		*path;
	char		**envp_array;
	struct stat	statbuf;
	int			err;

	path = find_command_path(cmd->argv[0], shell);
	if (!path)
		handle_command_not_found(cmd->argv[0]);
	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
		handle_directory_error(path);
	envp_array = env_list_to_array(shell->env_list);
	execve(path, cmd->argv, envp_array);
	err = errno;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
	free(path);
	ft_split_free(envp_array);
	if (err == EACCES)
		exit(126);
	exit(127);
}
