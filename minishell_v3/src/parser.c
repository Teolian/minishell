/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:31:27 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:59:31 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_seq(t_token **tokens, t_shell *shell);
static t_cmd	*parse_pipe(t_token **tokens, t_shell *shell);
static t_cmd	*parse_exec(t_token **tokens, t_shell *shell);
static t_cmd	*parse_exec_loop(t_token **tokens, t_shell *shell, t_cmd *cmd);

t_cmd	*parse_command(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	char	*msg1;
	char	*final_msg;

	cmd = parse_seq(tokens, shell);
	if (peek_type(tokens) != TOKEN_EOF)
	{
		msg1 = ft_strjoin("minishell: syntax error near unexpected token `",
				(*tokens)->value);
		final_msg = ft_strjoin(msg1, "'");
		ft_putendl_fd(final_msg, 2);
		free(msg1);
		free(final_msg);
		shell->exit_status = 2;
		free_ast(cmd);
		return (NULL);
	}
	return (cmd);
}

static t_cmd	*parse_seq(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parse_pipe(tokens, shell);
	if (!cmd)
		return (NULL);
	if (peek_type(tokens) == TOKEN_SEMICOLON)
	{
		consume_token(tokens);
		if (peek_type(tokens) == TOKEN_EOF
			|| peek_type(tokens) == TOKEN_SEMICOLON)
			return (parser_error("Syntax error near unexpected token `;'",
					shell, cmd));
		right_cmd = parse_seq(tokens, shell);
		if (!right_cmd)
		{
			free_ast(cmd);
			return (NULL);
		}
		cmd = new_seq_cmd(cmd, right_cmd);
	}
	return (cmd);
}

static t_cmd	*parse_pipe(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parse_exec(tokens, shell);
	if (!cmd)
		return (NULL);
	if (peek_type(tokens) == TOKEN_PIPE)
	{
		consume_token(tokens);
		if (peek_type(tokens) == TOKEN_EOF || peek_type(tokens) == TOKEN_PIPE)
			return (parser_error("Syntax error near unexpected token `|'",
					shell, cmd));
		right_cmd = parse_pipe(tokens, shell);
		if (!right_cmd)
		{
			free_ast(cmd);
			return (NULL);
		}
		cmd = new_pipe_cmd(cmd, right_cmd);
	}
	return (cmd);
}

static t_cmd	*parse_exec(t_token **tokens, t_shell *shell)
{
	t_exec_cmd	*ecmd;
	t_cmd		*cmd;

	cmd = new_exec_cmd();
	if (!cmd)
		return (NULL);
	ecmd = (t_exec_cmd *)cmd;
	cmd = parse_exec_loop(tokens, shell, cmd);
	if (!cmd)
		return (NULL);
	if (cmd->type == NODE_EXEC && (ecmd->argv == NULL || ecmd->argv[0] == NULL))
	{
		free_ast(cmd);
		return (NULL);
	}
	return (cmd);
}

static t_cmd	*parse_exec_loop(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	t_exec_cmd	*ecmd;

	ecmd = (t_exec_cmd *)cmd;
	while (peek_type(tokens) != TOKEN_PIPE && peek_type(tokens) != TOKEN_EOF
		&& peek_type(tokens) != TOKEN_SEMICOLON)
	{
		if (peek_type(tokens) == TOKEN_WORD)
		{
			add_arg_to_exec_cmd(ecmd, ft_strdup((*tokens)->value));
			consume_token(tokens);
		}
		else
		{
			cmd = handle_redirection(tokens, shell, cmd);
			if (!cmd)
				return (NULL);
		}
	}
	return (cmd);
}
