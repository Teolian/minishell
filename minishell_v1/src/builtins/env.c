/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:05:56 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:56:24 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_var(void *content)
{
	t_env	*env_var;

	env_var = (t_env *)content;
	if (env_var && env_var->key && env_var->value)
	{
		ft_putstr_fd(env_var->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(env_var->value, 1);
	}
}

/*
** ft_env
** Implements the env command.
** It now iterates through the t_list in the shell struct.
*/
int	ft_env(t_shell *shell)
{
	if (!shell || !shell->env_list)
		return (1);
	ft_lstiter(shell->env_list, &print_env_var);
	return (0);
}
