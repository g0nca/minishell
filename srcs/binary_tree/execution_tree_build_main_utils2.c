/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main_utils2.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:23:10 by joaomart          #+#    #+#             */
/*   Updated: 2025/09/24 10:27:09 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_heredoc_tree(t_token *curr, t_shell *shell, t_redirs *redirs)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		redirs->in = create_heredoc(curr->next->value, shell);
		if (!redirs->in)
			return (-1);
	}
	return (0);
}

int	handle_input_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell, t_redirs *redirs)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		redirs->in = curr->next->value;
		if (open_input_file(cmd, curr->next->value, shell) < 0)
			return (-1);
	}
	return (0);
}

int	handle_output_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell, t_redirs *redirs)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		redirs->out = curr->next->value;
		if (open_output_file(cmd, curr->next->value, false, shell) < 0)
			return (-1);
	}
	return (0);
}

int	handle_append_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell, t_redirs *redirs)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		redirs->append = curr->next->value;
		if (open_output_file(cmd, curr->next->value, true, shell) < 0)
			return (-1);
	}
	return (0);
}
