/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-03 14:48:42 by npugach           #+#    #+#             */
/*   Updated: 2025-09-03 14:48:42 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_temp_filename(void)
{
	static int	counter = 0;
	char		*num_str;
	char		*filename;
	char		*temp;

	num_str = ft_itoa(getpid() + counter++);
	temp = ft_strjoin("/tmp/.heredoc_", num_str);
	filename = ft_strjoin(temp, ".tmp");
	free(num_str);
	free(temp);
	return (filename);
}

static int	read_heredoc_to_tempfile(char *delimiter, char *temp_file)
{
	int		temp_fd;
	char	*line;
	size_t	delimiter_len;

	temp_fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (temp_fd < 0)
		return (-1);
	delimiter_len = ft_strlen(delimiter);
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			line = readline("> ");
			if (!line || (ft_strlen(line) == delimiter_len
					&& ft_strncmp(line, delimiter, delimiter_len) == 0))
			{
				if (line)
					free(line);
				break ;
			}
			ft_putendl_fd(line, temp_fd);
			free(line);
		}
	}
	else
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line)
				break ;
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			if (ft_strlen(line) == delimiter_len
				&& ft_strncmp(line, delimiter, delimiter_len) == 0)
			{
				free(line);
				break ;
			}
			ft_putendl_fd(line, temp_fd);
			free(line);
			ft_putstr_fd("> ", STDERR_FILENO);
		}
	}
	close(temp_fd);
	return (0);
}

int	process_heredoc(t_redir_cmd *redir, t_shell *shell)
{
	char	*temp_file;
	int		fd;

	(void)shell;
	temp_file = create_temp_filename();
	if (!temp_file)
		return (-1);
	if (read_heredoc_to_tempfile(redir->file, temp_file) < 0)
	{
		free(temp_file);
		return (-1);
	}
	fd = open(temp_file, O_RDONLY);
	unlink(temp_file);
	free(temp_file);
	return (fd);
}
