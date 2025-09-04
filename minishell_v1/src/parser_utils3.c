/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:10:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:59:04 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*create_redir_command(t_token_type type, char *file, t_cmd *cmd)
{
	if (type == TOKEN_REDIR_IN)
		cmd = new_redir_cmd(cmd, file, O_RDONLY, 0);
	else if (type == TOKEN_REDIR_OUT)
		cmd = new_redir_cmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (type == TOKEN_REDIR_APPEND)
		cmd = new_redir_cmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (type == TOKEN_HEREDOC)
		cmd = new_redir_cmd(cmd, file, O_HEREDOC, 0);
	else
		free(file);
	return (cmd);
}

t_cmd	*handle_redirection(t_token **tokens, t_shell *shell, t_cmd *cmd)
{
	t_token_type	type;
	char			*file;

	type = peek_type(tokens);
	consume_token(tokens);
	if (peek_type(tokens) != TOKEN_WORD)
	{
		free_ast(cmd);
		ft_putendl_fd("Syntax error: expected file after redirection", 2);
		shell->exit_status = 2;
		return (NULL);
	}
	file = (*tokens)->value;
	(*tokens)->value = NULL;
	cmd = create_redir_command(type, file, cmd);
	consume_token(tokens);
	return (cmd);
}

void	*parser_error(char *s, t_shell *shell, t_cmd *cmd)
{
	ft_putendl_fd(s, 2);
	shell->exit_status = 2;
	free_ast(cmd);
	return (NULL);
}
