/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main_utils2.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:23:10 by joaomart          #+#    #+#             */
/*   Updated: 2025/09/29 14:03:36 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_heredoc_tree(t_token *curr, t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		shell->in = create_heredoc(curr->next->value, shell);
		if (!shell->in)
			return (-1);
	}
	return (0);
}

int	handle_input_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		shell->in = curr->next->value;
		if (open_input_file(cmd, curr->next->value, shell) < 0)
			return (-1);
	}
	return (0);
}

int	handle_output_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		shell->out = curr->next->value;
		if (open_output_file(cmd, curr->next->value, false, shell) < 0)
			return (-1);
	}
	return (0);
}

int	handle_append_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		shell->append = curr->next->value;
		if (open_output_file(cmd, curr->next->value, true, shell) < 0)
			return (-1);
	}
	return (0);
}
