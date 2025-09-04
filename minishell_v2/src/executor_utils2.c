/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:00:04 by juwang            #+#    #+#             */
/*   Updated: 2025/09/04 17:29:45 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_loop(int pipe_write_fd, const char *delimiter)
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putendl_fd("minishell: warning: document delimited by EOF", 2);
			break ;
		}
		if (ft_strlen(line) == delimiter_len + 1
			&& ft_strncmp(line, delimiter, delimiter_len) == 0)
			break ;
		ft_putstr_fd(line, pipe_write_fd);
		free(line);
	}
	if (line)
		free(line);
}

static int	handle_heredoc_redirection(t_redir_cmd *redir)
{
	int	p[2];

	if (pipe(p) < 0)
		return (-1);
	heredoc_loop(p[1], redir->file);
	close(p[1]);
	return (p[0]);
}

static int	handle_regular_redirection(t_redir_cmd *redir, t_shell *shell)
{
	char	*expanded_file;
	int		fd;

	expanded_file = perform_expansion(redir->file, shell);
	fd = open(expanded_file, redir->mode, 0644);
	free(expanded_file);
	if (fd < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	handle_single_redirection(t_redir_cmd *redir, t_shell *shell)
{
	int	fd;

	if (redir->mode == O_HEREDOC)
		fd = handle_heredoc_redirection(redir);
	else
		fd = handle_regular_redirection(redir, shell);
	if (fd < 0)
		return (0);
	if (dup2(fd, redir->fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
