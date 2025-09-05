/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:50:23 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:58:32 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_operator(const char *s, int i, t_token **toks);
static int	handle_word(const char *s, int i, t_token **toks);
static void	tokenize_line(const char *line, t_token **tokens);

t_token	*lexer(const char *line, t_shell *shell)
{
	t_token	*tokens;

	(void)shell;
	tokens = NULL;
	tokenize_line(line, &tokens);
	add_token_back(&tokens, new_token(TOKEN_EOF, ft_strdup("EOF")));
	return (tokens);
}

static void	tokenize_line(const char *line, t_token **tokens)
{
	int	i;
	int	consumed;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(" \t\n\v\f\r", line[i]))
		{
			i++;
			continue ;
		}
		consumed = handle_operator(line, i, tokens);
		if (consumed > 0)
			i += consumed;
		else
		{
			consumed = handle_word(line, i, tokens);
			i += consumed;
		}
	}
}

static int	handle_operator(const char *s, int i, t_token **toks)
{
	if (s[i] == '>')
		return (handle_greater(s, i, toks));
	if (s[i] == '<')
		return (handle_less(s, i, toks));
	if (s[i] == '|')
	{
		add_token_back(toks, new_token(TOKEN_PIPE, ft_strdup("|")));
		return (1);
	}
	if (s[i] == ';')
	{
		add_token_back(toks, new_token(TOKEN_SEMICOLON, ft_strdup(";")));
		return (1);
	}
	return (0);
}

static int	handle_word(const char *s, int i, t_token **toks)
{
	int		start;
	char	quote;

	start = i;
	quote = 0;
	while (s[i])
	{
		if (quote == 0 && ft_strchr(" \t\n\v\f\r<>|;", s[i]))
			break ;
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = s[i];
		else if (quote != 0 && s[i] == quote)
			quote = 0;
		i++;
	}
	add_token_back(toks, new_token(TOKEN_WORD, ft_substr(s, start, i - start)));
	return (i - start);
}
