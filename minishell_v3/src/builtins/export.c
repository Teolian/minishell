/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:07:20 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:55:19 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_valid_identifier(const char *s);
void		print_sorted_env(t_shell *shell);
static int	add_or_update_env(char *arg, t_shell *shell);

int	ft_export(char **args, t_shell *shell)
{
	int	i;
	int	ret;

	ret = 0;
	if (!args[1])
	{
		print_sorted_env(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!add_or_update_env(args[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}

static void	parse_env_arg(char *arg, char **key, char **value)
{
	char	*eq_ptr;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr)
	{
		*key = ft_substr(arg, 0, eq_ptr - arg);
		*value = ft_strdup(eq_ptr + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

static int	add_or_update_env(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;

	parse_env_arg(arg, &key, &value);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(key);
		if (value)
			free(value);
		return (0);
	}
	set_env_value(shell, key, value);
	free(key);
	if (value)
		free(value);
	return (1);
}
