/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:40:58 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:58:45 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_exec_cmd(void)
{
	t_exec_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*new_redir_cmd(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redir_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*new_pipe_cmd(t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*new_seq_cmd(t_cmd *left, t_cmd *right)
{
	t_seq_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_SEQ;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

void	consume_token(t_token **tokens)
{
	if (tokens && *tokens)
		*tokens = (*tokens)->next;
}
