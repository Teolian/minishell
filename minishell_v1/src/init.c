/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:03:06 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:58:03 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		update_existing_env(t_env *env_var, char *value);
void		create_new_env(t_shell *shell, char *key, char *value);
void		parse_and_set_env(t_shell *shell, char *envp_line);
static void	free_env_var(void *content);

void	init_shell(t_shell *shell, char **envp)
{
	int	i;

	shell->env_list = NULL;
	shell->exit_status = 0;
	i = 0;
	while (envp && envp[i])
	{
		parse_and_set_env(shell, envp[i]);
		i++;
	}
}

void	free_shell(t_shell *shell)
{
	if (shell && shell->env_list)
	{
		ft_lstclear(&shell->env_list, free_env_var);
	}
}

static void	free_env_var(void *content)
{
	t_env	*env_var;

	env_var = (t_env *)content;
	if (env_var)
	{
		free(env_var->key);
		free(env_var->value);
		free(env_var);
	}
}

void	set_env_value(t_shell *shell, char *key, char *value)
{
	t_list	*current;
	t_env	*env_var;

	current = shell->env_list;
	while (current)
	{
		env_var = (t_env *)current->content;
		if (ft_strncmp(env_var->key, key, ft_strlen(key) + 1) == 0)
		{
			update_existing_env(env_var, value);
			return ;
		}
		current = current->next;
	}
	create_new_env(shell, key, value);
}
