/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main_utils2.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:23:10 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/28 09:07:35 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_heredoc_tree(t_token *curr, t_shell *shell, t_exec_node *cmd)
{
	(void)shell;
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		if (update_delimiters_array(cmd, curr->next->value) == -1)
			return (-1);
		cmd->last_redir_in = curr->next->value;
		cmd->last_redir_in_type = 6;
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
		if (cmd->last_redir_in != NULL && cmd->last_redir_in_type != 0)
		{
			cmd->last_redir_in = NULL;
			cmd->last_redir_in_type = 0;
		}
		cmd->last_redir_in = curr->next->value;
		cmd->last_redir_in_type = 3;
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
