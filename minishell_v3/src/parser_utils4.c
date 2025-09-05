/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:20:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:59:06 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **argv)
{
	int	i;

	i = 0;
	if (argv)
		while (argv[i])
			i++;
	return (i);
}

void	add_arg_to_exec_cmd(t_exec_cmd *ecmd, char *arg)
{
	int		i;
	int		arg_count;
	char	**new_argv;

	arg_count = count_args(ecmd->argv);
	new_argv = ft_calloc(arg_count + 2, sizeof(char *));
	if (!new_argv)
		return ;
	i = 0;
	if (ecmd->argv)
	{
		while (ecmd->argv[i])
		{
			new_argv[i] = ecmd->argv[i];
			i++;
		}
	}
	new_argv[i] = arg;
	new_argv[i + 1] = NULL;
	free(ecmd->argv);
	ecmd->argv = new_argv;
}
