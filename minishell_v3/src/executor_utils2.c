/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:00:04 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:54:45 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	handle_directory_error(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free(path);
	exit(126);
}

int	handle_single_redirection(t_redir_cmd *redir, t_shell *shell)
{
	char	*expanded_file;
	int		fd;

	expanded_file = perform_expansion(redir->file, shell);
	if (redir->mode == O_HEREDOC)
		fd = handle_heredoc(redir);
	else
		fd = open(expanded_file, redir->mode, 0644);
	if (fd < 0)
	{
		perror(expanded_file);
		shell->exit_status = 1;
		free(expanded_file);
		return (0);
	}
	if (dup2(fd, redir->fd) == -1)
	{
		perror("dup2");
		close(fd);
		free(expanded_file);
		return (0);
	}
	close(fd);
	free(expanded_file);
	return (1);
}
