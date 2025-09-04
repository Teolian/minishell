/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:10:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/13 16:49:54 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**ft_lst_to_array(t_list *lst)
{
	char	**array;
	int		i;
	t_list	*current;

	array = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = lst;
	while (current)
	{
		array[i] = ft_strdup((char *)current->content);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	append_str(char **s1, char *s2)
{
	char	*new;

	if (!s2)
		return ;
	if (!*s1)
	{
		*s1 = ft_strdup(s2);
		return ;
	}
	new = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = new;
}

char	*handle_tilde_expansion(char *arg, t_shell *shell)
{
	char	*home;
	char	*processed_arg;

	if (arg[0] == '~' && (arg[1] == '\0' || arg[1] == '/'))
	{
		home = get_env_value(shell->env_list, "HOME");
		if (home)
			processed_arg = ft_strjoin(home, arg + 1);
		else
			processed_arg = ft_strdup(arg);
	}
	else
		processed_arg = ft_strdup(arg);
	return (processed_arg);
}

int	is_quoted(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[0] == '"' && str[len - 1] == '"')
		return (1);
	if (str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	return (0);
}

t_list	*split_string_to_list(char *expanded_str)
{
	char	**split_arr;
	t_list	*split_list;
	t_list	*new_node;
	int		i;

	split_arr = ft_split(expanded_str, ' ');
	free(expanded_str);
	if (!split_arr)
		return (NULL);
	split_list = NULL;
	i = 0;
	while (split_arr[i])
	{
		new_node = ft_lstnew(split_arr[i]);
		if (!new_node)
		{
			ft_lstclear(&split_list, free);
			ft_split_free(split_arr);
			return (NULL);
		}
		ft_lstadd_back(&split_list, new_node);
		i++;
	}
	free(split_arr);
	return (split_list);
}
