/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:10:10 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:55:26 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env_array(t_env **array, int count)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(array[j]->key, array[j + 1]->key, -1) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_env_entry(t_env *env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	if (env->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

void	print_sorted_env(t_shell *shell)
{
	t_list	*current;
	t_env	**env_array;
	int		count;
	int		i;

	count = ft_lstsize(shell->env_list);
	env_array = ft_calloc(count, sizeof(t_env *));
	if (!env_array)
		return ;
	current = shell->env_list;
	i = 0;
	while (current)
	{
		env_array[i++] = (t_env *)current->content;
		current = current->next;
	}
	sort_env_array(env_array, count);
	i = 0;
	while (i < count)
		print_env_entry(env_array[i++]);
	free(env_array);
}

int	is_valid_identifier(const char *s)
{
	if (!s || (!ft_isalpha(*s) && *s != '_'))
		return (0);
	s++;
	while (*s)
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}
