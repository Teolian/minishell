/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:08:33 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 15:04:51 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*expand_and_split(char *arg, t_shell *shell)
{
	char	*expanded_str;
	t_list	*nodes;
	char	**split_arr;
	int		i;
	int		has_quotes_originally;

	has_quotes_originally = ft_strchr(arg, '\'') || ft_strchr(arg, '"');
	expanded_str = perform_expansion(arg, shell);
	if (!expanded_str)
		return (NULL);
	if (has_quotes_originally || ft_strlen(expanded_str) == 0)
	{
		nodes = ft_lstnew(expanded_str);
		return (nodes);
	}
	split_arr = ft_split(expanded_str, ' ');
	free(expanded_str);
	if (!split_arr)
		return (NULL);
	nodes = NULL;
	i = 0;
	while (split_arr[i])
		ft_lstadd_back(&nodes, ft_lstnew(split_arr[i++]));
	free(split_arr);
	return (nodes);
}

void	expand_command_args(t_exec_cmd *cmd, t_shell *shell)
{
	t_list	*new_args;
	t_list	*current_nodes;
	int		i;

	if (!cmd || !cmd->argv)
		return ;
	new_args = NULL;
	i = 0;
	while (cmd->argv[i])
	{
		current_nodes = expand_and_split(cmd->argv[i], shell);
		if (current_nodes)
			ft_lstadd_back(&new_args, current_nodes);
		i++;
	}
	ft_split_free(cmd->argv);
	cmd->argv = ft_lst_to_array(new_args);
	ft_lstclear(&new_args, free);
}
