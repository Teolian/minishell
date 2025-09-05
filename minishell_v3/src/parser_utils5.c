/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:52:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/16 17:59:24 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	peek_type(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (TOKEN_EOF);
	return ((*tokens)->type);
}

void	consume_token(t_token **tokens)
{
	if (tokens && *tokens)
		*tokens = (*tokens)->next;
}
