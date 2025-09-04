/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:26:06 by npugach           #+#    #+#             */
/*   Updated: 2025/09/03 19:26:54 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_cmd(t_and_cmd *acmd)
{
	free_ast(acmd->left);
	free_ast(acmd->right);
}

void	free_or_cmd(t_or_cmd *ocmd)
{
	free_ast(ocmd->left);
	free_ast(ocmd->right);
}
