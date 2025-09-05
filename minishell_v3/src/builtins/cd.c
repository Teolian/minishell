/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:08:28 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:55:58 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cd_path(char **args, t_shell *shell);
int		do_chdir(char *path, t_shell *shell);

/*
** ft_cd
** Implements the cd command.
*/
int	ft_cd(char **args, t_shell *shell)
{
	char	*path;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = get_cd_path(args, shell);
	if (!path)
		return (1);
	return (do_chdir(path, shell));
}
