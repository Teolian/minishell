/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:25:04 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:57:49 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_existing_env(t_env *env_var, char *value)
{
	free(env_var->value);
	if (value)
		env_var->value = ft_strdup(value);
	else
		env_var->value = ft_strdup("");
}

void	create_new_env(t_shell *shell, char *key, char *value)
{
	t_env	*env_var;

	env_var = ft_calloc(1, sizeof(t_env));
	if (!env_var)
		return ;
	env_var->key = ft_strdup(key);
	if (value)
		env_var->value = ft_strdup(value);
	else
		env_var->value = ft_strdup("");
	ft_lstadd_back(&shell->env_list, ft_lstnew(env_var));
}

void	parse_and_set_env(t_shell *shell, char *envp_line)
{
	char	*key;
	char	*value;
	char	*eq_ptr;

	eq_ptr = ft_strchr(envp_line, '=');
	if (eq_ptr)
	{
		key = ft_substr(envp_line, 0, eq_ptr - envp_line);
		value = ft_strdup(eq_ptr + 1);
		set_env_value(shell, key, value);
		free(key);
		free(value);
	}
}
