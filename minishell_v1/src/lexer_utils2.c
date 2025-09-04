/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:58:00 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 19:11:08 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_greater(const char *s, int i, t_token **toks)
{
	if (s[i + 1] == '>')
	{
		add_token_back(toks, new_token(TOKEN_REDIR_APPEND, ft_strdup(">>")));
		return (2);
	}
	add_token_back(toks, new_token(TOKEN_REDIR_OUT, ft_strdup(">")));
	return (1);
}

int	handle_less(const char *s, int i, t_token **toks)
{
	if (s[i + 1] == '<')
	{
		add_token_back(toks, new_token(TOKEN_HEREDOC, ft_strdup("<<")));
		return (2);
	}
	add_token_back(toks, new_token(TOKEN_REDIR_IN, ft_strdup("<")));
	return (1);
}

int	handle_and_or(const char *s, int i, t_token **toks)
{
	if (s[i] == '&' && s[i + 1] == '&')
	{
		add_token_back(toks, new_token(TOKEN_AND, ft_strdup("&&")));
		return (2);
	}
	if (s[i] == '|' && s[i + 1] == '|')
	{
		add_token_back(toks, new_token(TOKEN_OR, ft_strdup("||")));
		return (2);
	}
	return (0);
}
