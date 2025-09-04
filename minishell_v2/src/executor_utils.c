/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:00:30 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:54:49 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env_by_key(t_list *env_list, const char *key)
{
	t_list	*current;
	t_env	*env_var;
	size_t	key_len;

	current = env_list;
	key_len = ft_strlen(key);
	while (current)
	{
		env_var = (t_env *)current->content;
		if (ft_strlen(env_var->key) == key_len && ft_strncmp(env_var->key, key,
				key_len) == 0)
			return (env_var);
		current = current->next;
	}
	return (NULL);
}

char	*get_env_value(t_list *env_list, const char *key)
{
	t_env	*env_var;

	env_var = get_env_by_key(env_list, key);
	if (env_var)
		return (env_var->value);
	return (NULL);
}

char	**env_list_to_array(t_list *env_list)
{
	char	**array;
	t_list	*current;
	char	*tmp;
	int		i;
	t_env	*env_var;

	array = ft_calloc(ft_lstsize(env_list) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		env_var = (t_env *)current->content;
		tmp = ft_strjoin(env_var->key, "=");
		array[i] = ft_strjoin(tmp, env_var->value);
		free(tmp);
		current = current->next;
		i++;
	}
	return (array);
}

static char	*search_in_path(const char *cmd, char *path_env)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_split_free(paths);
			return (full_path);
		}
		free(full_path);
	}
	ft_split_free(paths);
	return (NULL);
}

char	*find_command_path(const char *cmd, t_shell *shell)
{
	char	*path_env;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		return (ft_strdup(cmd));
	}
	path_env = get_env_value(shell->env_list, "PATH");
	if (!path_env)
		return (NULL);
	return (search_in_path(cmd, path_env));
}
