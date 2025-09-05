/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:08:33 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:57:36 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static t_list	*expand_and_split_arg(char *arg, t_shell *shell);
static void		remove_empty_args(t_list **args);
static void		handle_empty_node(t_list **current, t_list **prev,
					t_list **args);

void	expand_command_args(t_exec_cmd *cmd, t_shell *shell)
{
	t_list	*new_args;
	int		i;
	t_list	*expanded_nodes;

	if (!cmd->argv || !cmd->argv[0])
		return ;
	new_args = NULL;
	i = 0;
	while (cmd->argv[i])
	{
		expanded_nodes = expand_and_split_arg(cmd->argv[i], shell);
		if (expanded_nodes)
			ft_lstadd_back(&new_args, expanded_nodes);
		i++;
	}
	remove_empty_args(&new_args);
	ft_split_free(cmd->argv);
	cmd->argv = ft_lst_to_array(new_args);
	ft_lstclear(&new_args, free);
}

static t_list	*expand_and_split_arg(char *arg, t_shell *shell)
{
	char	*processed_arg;
	char	*expanded_str;
	int		no_split;

	processed_arg = handle_tilde_expansion(arg, shell);
	if (!processed_arg)
		return (NULL);
	no_split = is_quoted(processed_arg)
		|| (ft_strchr(processed_arg, '=') != NULL);
	expanded_str = perform_expansion(processed_arg, shell);
	free(processed_arg);
	if (!expanded_str)
		return (NULL);
	if (no_split)
		return (ft_lstnew(expanded_str));
	return (split_string_to_list(expanded_str));
}

static void	handle_empty_node(t_list **current, t_list **prev, t_list **args)
{
	if (*prev)
		(*prev)->next = (*current)->next;
	else
		*args = (*current)->next;
	ft_lstdelone(*current, free);
	if (*prev)
		*current = (*prev)->next;
	else
		*current = *args;
}

static void	remove_empty_args(t_list **args)
{
	t_list	*current;
	t_list	*prev;

	current = *args;
	prev = NULL;
	while (current)
	{
		if (ft_strlen((char *)current->content) == 0)
			handle_empty_node(&current, &prev, args);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
