/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:37:38 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:58:54 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_exec_cmd(t_exec_cmd *ecmd);
static void	free_redir_cmd(t_redir_cmd *rcmd);
static void	free_pipe_cmd(t_pipe_cmd *pcmd);
static void	free_seq_cmd(t_seq_cmd *scmd);

void	free_ast(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == NODE_PIPE)
		free_pipe_cmd((t_pipe_cmd *)cmd);
	else if (cmd->type == NODE_SEQ)
		free_seq_cmd((t_seq_cmd *)cmd);
	else if (cmd->type == NODE_REDIR)
		free_redir_cmd((t_redir_cmd *)cmd);
	else if (cmd->type == NODE_EXEC)
		free_exec_cmd((t_exec_cmd *)cmd);
	free(cmd);
}

static void	free_exec_cmd(t_exec_cmd *ecmd)
{
	int	i;

	i = 0;
	while (ecmd->argv && ecmd->argv[i])
	{
		free(ecmd->argv[i]);
		i++;
	}
	free(ecmd->argv);
}

static void	free_redir_cmd(t_redir_cmd *rcmd)
{
	free_ast(rcmd->cmd);
	free(rcmd->file);
}

static void	free_pipe_cmd(t_pipe_cmd *pcmd)
{
	free_ast(pcmd->left);
	free_ast(pcmd->right);
}

static void	free_seq_cmd(t_seq_cmd *scmd)
{
	free_ast(scmd->left);
	free_ast(scmd->right);
}
