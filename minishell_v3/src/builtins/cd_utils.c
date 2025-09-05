/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:01:43 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:55:47 by juwang           ###   ########.fr       */
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

static int	handle_dotdot(char *original_path)
{
	char	cwd[1024];
	char	*last_slash;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (chdir(original_path));
	last_slash = ft_strrchr(cwd, '/');
	if (last_slash == cwd && *(cwd + 1) != '\0')
		*(last_slash + 1) = '\0';
	else if (last_slash != NULL && last_slash != cwd)
		*last_slash = '\0';
	return (chdir(cwd));
}

int	do_chdir(char *path, t_shell *shell)
{
	int	ret;

	(void)shell;
	if (ft_strncmp(path, "..", 3) == 0)
		ret = handle_dotdot(path);
	else
		ret = chdir(path);
	if (ret != 0)
		return (cd_error(path));
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

char	*get_cd_path(char **args, t_shell *shell)
{
	if (args[1] == NULL)
		return (get_home_path(shell));
	return (args[1]);
}
