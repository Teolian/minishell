/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:00:04 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 19:39:12 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_free(char **split_array)
{
	int	i;

	if (!split_array)
		return ;
	i = 0;
	while (split_array[i])
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}

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

	if (redir->mode == O_HEREDOC)
	{
		fd = process_heredoc(redir, shell);
	}
	else
	{
		expanded_file = perform_expansion(redir->file, shell);
		fd = open(expanded_file, redir->mode, 0644);
		free(expanded_file);
	}
	if (fd < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return (0);
	}
	if (dup2(fd, redir->fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
