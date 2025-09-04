/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:07:08 by npugach           #+#    #+#             */
/*   Updated: 2025/09/04 16:17:51 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_exec(t_token **tokens, t_shell *shell);

static int	should_continue_parsing(t_token **tokens)
{
	t_token_type	type;

	type = peek_type(tokens);
	if (type == TOKEN_PIPE || type == TOKEN_EOF || type == TOKEN_SEMICOLON)
		return (0);
	if (type == TOKEN_AND || type == TOKEN_OR)
		return (0);
	return (1);
}

static t_cmd	*process_exec_token(t_token **tokens,
	t_shell *shell, t_cmd *cmd)
{
	char	*arg;

	if (peek_type(tokens) == TOKEN_WORD)
	{
		arg = ft_strdup((*tokens)->value);
		add_arg_to_exec_cmd((t_exec_cmd *)cmd, arg);
		consume_token(tokens);
	}
	else
	{
		cmd = handle_redirection(tokens, shell, cmd);
		if (!cmd)
			return (NULL);
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
	while (should_continue_parsing(tokens))
	{
		cmd = process_exec_token(tokens, shell, cmd);
		if (!cmd)
			return (NULL);
	}
	ecmd = (t_exec_cmd *)cmd;
	if (cmd->type == NODE_EXEC && (!ecmd->argv || !ecmd->argv[0]))
	{
		free_ast(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*parse_pipe(t_token **tokens, t_shell *shell)
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
