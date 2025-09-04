/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:31:02 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 19:28:41 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	if (cmd->type == NODE_PIPE)
		execute_pipe_cmd((t_pipe_cmd *)cmd, shell);
	else if (cmd->type == NODE_AND)
		execute_and_cmd((t_and_cmd *)cmd, shell);
	else if (cmd->type == NODE_OR)
		execute_or_cmd((t_or_cmd *)cmd, shell);
	else if (cmd->type == NODE_SEQ)
		execute_seq_cmd((t_seq_cmd *)cmd, shell);
	else
		execute_simple_command(cmd, shell, 0);
}

void	execute_simple_command(t_cmd *cmd, t_shell *shell, int in_pipe)
{
	t_list		*redir_list;
	t_exec_cmd	*ecmd;
	t_cmd		*current_cmd;

	redir_list = NULL;
	current_cmd = cmd;
	while (current_cmd && current_cmd->type == NODE_REDIR)
	{
		ft_lstadd_front(&redir_list, ft_lstnew(current_cmd));
		current_cmd = ((t_redir_cmd *)current_cmd)->cmd;
	}
	ecmd = (t_exec_cmd *)current_cmd;
	if (ecmd)
		expand_command_args(ecmd, shell);
	if (ecmd && ecmd->argv && ecmd->argv[0]
		&& is_parent_builtin(ecmd->argv[0]) && !in_pipe)
		execute_parent_builtin(ecmd, redir_list, shell);
	else
		execute_forked_command(ecmd, redir_list, shell);
	ft_lstclear(&redir_list, NULL);
}

int	apply_redirections(t_list *redir_list, t_shell *shell)
{
	t_list		*current;
	t_redir_cmd	*redir;

	current = redir_list;
	while (current)
	{
		redir = (t_redir_cmd *)current->content;
		if (!handle_single_redirection(redir, shell))
			return (0);
		current = current->next;
	}
	return (1);
}

void	execute_in_child(t_exec_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	if (cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL
		|| cmd->argv[0][0] == '\0')
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		exit_code = dispatch_builtin(cmd, shell);
		exit(exit_code);
	}
	prepare_and_exec_command(cmd, shell);
}
