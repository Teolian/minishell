/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:08:28 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 19:23:37 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cd_path(char **args, t_shell *shell);
int		do_chdir(char *path, t_shell *shell);

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	path = get_cd_path(args, shell);
	if (!path)
	{
		shell->exit_status = 1;
		return (1);
	}
	if (do_chdir(path, shell) != 0)
	{
		shell->exit_status = 1;
		return (1);
	}
	shell->exit_status = 0;
	return (0);
}
