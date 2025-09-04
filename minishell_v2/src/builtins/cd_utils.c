/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:01:43 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 19:41:33 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int	do_chdir(char *path, t_shell *shell)
{
	char	*old_pwd;
	char	cwd[1024];

	old_pwd = get_env_value(shell->env_list, "PWD");
	if (chdir(path) != 0)
		return (cd_error(path));
	if (old_pwd)
		set_env_value(shell, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_value(shell, "PWD", cwd);
	return (0);
}

static char	*get_home_path(t_shell *shell)
{
	char	*path;

	path = get_env_value(shell->env_list, "HOME");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (path);
}

static char	*expand_tilde_path(char *arg, t_shell *shell)
{
	char	*home;
	char	*result;

	if (arg[0] == '~')
	{
		if (arg[1] == '\0' || arg[1] == '/')
		{
			home = get_env_value(shell->env_list, "HOME");
			if (!home)
			{
				ft_putstr_fd("minishell: cd: HOME not set\n", 2);
				return (NULL);
			}
			if (arg[1] == '\0')
				return (home);
			result = ft_strjoin(home, arg + 1);
			return (result);
		}
	}
	return (arg);
}

char	*get_cd_path(char **args, t_shell *shell)
{
	if (args[1] == NULL)
		return (get_home_path(shell));
	return (expand_tilde_path(args[1], shell));
}
