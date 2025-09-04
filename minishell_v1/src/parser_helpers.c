/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-03 14:49:51 by npugach           #+#    #+#             */
/*   Updated: 2025-09-03 14:49:51 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*handle_and_token(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	t_cmd	*right_cmd;

	consume_token(tokens);
	if (peek_type(tokens) == TOKEN_EOF)
		return (parser_error("Syntax error near unexpected token `&&'",
				shell, cmd));
	right_cmd = parse_and_or(tokens, shell);
	if (!right_cmd)
	{
		free_ast(cmd);
		return (NULL);
	}
	return (new_and_cmd(cmd, right_cmd));
}

t_cmd	*handle_or_token(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	t_cmd	*right_cmd;

	consume_token(tokens);
	if (peek_type(tokens) == TOKEN_EOF)
		return (parser_error("Syntax error near unexpected token `||'",
				shell, cmd));
	right_cmd = parse_and_or(tokens, shell);
	if (!right_cmd)
	{
		free_ast(cmd);
		return (NULL);
	}
	return (new_or_cmd(cmd, right_cmd));
}

int	should_continue_parsing(t_token **tokens)
{
	t_token_type	type;

	type = peek_type(tokens);
	return (type != TOKEN_PIPE && type != TOKEN_EOF
		&& type != TOKEN_SEMICOLON && type != TOKEN_AND
		&& type != TOKEN_OR);
}
