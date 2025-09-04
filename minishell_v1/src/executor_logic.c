/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:24:47 by npugach           #+#    #+#             */
/*   Updated: 2025/09/03 19:25:00 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 18:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_and_cmd(t_and_cmd *cmd, t_shell *shell)
{
	execute_ast(cmd->left, shell);
	if (shell->exit_status == 0)
		execute_ast(cmd->right, shell);
}

void	execute_or_cmd(t_or_cmd *cmd, t_shell *shell)
{
	execute_ast(cmd->left, shell);
	if (shell->exit_status != 0)
		execute_ast(cmd->right, shell);
}

void	execute_seq_cmd(t_seq_cmd *cmd, t_shell *shell)
{
	execute_ast(cmd->left, shell);
	execute_ast(cmd->right, shell);
}
