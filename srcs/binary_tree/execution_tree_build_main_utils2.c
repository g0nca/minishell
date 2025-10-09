/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main_utils2.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:23:10 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/09 09:56:59 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_heredoc_tree(t_token *curr, t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		shell->heredoc = create_heredoc(curr->next->value, shell);
		if (!shell->heredoc)
			return (-1);
	}
	return (0);
}

int	handle_input_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		if (open_input_file(cmd, curr->next->value, shell) < 0)
			return (-1);
		cmd->input_file = curr->next->value;
		if (!cmd->input_file)
			return (-1);
	}
	return (0);
}

int	handle_output_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		if (open_output_file(cmd, curr->next->value, false, shell) < 0)
			return (-1);
		cmd->output_file = curr->next->value;
		if (!cmd->output_file)
			return (-1);
		cmd->append_file = NULL;
	}
	return (0);
}

int	handle_append_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		if (open_output_file(cmd, curr->next->value, true, shell) < 0)
			return (-1);
		cmd->append_file = curr->next->value;
		if (!cmd->append_file)
			return (-1);
		cmd->output_file = NULL;
	}
	return (0);
}
