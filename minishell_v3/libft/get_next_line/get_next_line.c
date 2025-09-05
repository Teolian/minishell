/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:34:21 by juwang            #+#    #+#             */
/*   Updated: 2025/05/21 18:40:23 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	init_remain_and_buffer(char **remain, char **buf)
{
	if (!*remain)
	{
		*remain = malloc(1);
		if (!*remain)
			return (0);
		(*remain)[0] = '\0';
	}
	*buf = malloc(BUFFER_SIZE + 1);
	if (!*buf)
	{
		free(*remain);
		return (0);
	}
	return (1);
}

static char	*read_and_store(int fd, char *remain)
{
	char	*buf;
	char	*tmp;
	int		bytes;

	if (!init_remain_and_buffer(&remain, &buf))
		return (NULL);
	bytes = 1;
	while (!ft_strchr(remain, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buf), free(remain), NULL);
		buf[bytes] = '\0';
		tmp = ft_strjoin(remain, buf);
		if (!tmp)
			return (free(buf), free(remain), NULL);
		free(remain);
		remain = tmp;
	}
	free(buf);
	return (remain);
}

static char	*extract_line(char *remain)
{
	char	*line;
	size_t	i;

	if (!remain || !remain[0])
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (remain[i] == '\n')
		i++;
	line = ft_substr(remain, 0, i);
	return (line);
}

static char	*update_remain(char *remain)
{
	size_t	i;
	size_t	j;
	char	*new_remain;

	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (!remain[i])
	{
		free(remain);
		return (NULL);
	}
	i++;
	new_remain = (char *)malloc(ft_strlen(remain + i) + 1);
	if (!new_remain)
		return (NULL);
	j = 0;
	while (remain[i])
		new_remain[j++] = remain[i++];
	new_remain[j] = '\0';
	free(remain);
	return (new_remain);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain = read_and_store(fd, remain);
	if (!remain)
		return (NULL);
	line = extract_line(remain);
	remain = update_remain(remain);
	return (line);
}
