/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:17:50 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:58:09 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	peek_type(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (TOKEN_EOF);
	return ((*tokens)->type);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token || !value)
	{
		free(value);
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token **tokens, t_token *new)
{
	t_token	*current;

	if (!tokens || !new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new;
}
