/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_redirect_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:10:37 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:12:23 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT || type == TOKEN_APPEND);
}

// Find the RIGHTMOST (last) redirection of each type to match bash behavior
t_token *find_last_redirection(t_token *start, t_token *end, t_token_type redir_type)
{
	t_token *curr;
	t_token *last_found;

	curr = start;
	last_found = NULL;
	while (curr && curr != end && curr->next)
	{
		if ((t_token_type)curr->type == redir_type && curr->next->type == TOKEN_WORD)
			last_found = curr;
		curr = curr->next;
	}
	return (last_found);
}

// Process all redirections in order, but only keep the last one of each type
t_exec_node	*create_redirect_node(t_token *start, t_token *curr, t_token *end)
{
	t_exec_node	*node;

	node = malloc(sizeof(t_exec_node));
	if (!node)
		return (NULL);
	(void)end;
	node->type = get_redirect_node_type(curr->type);
	node->cmd = malloc(sizeof(char *) * 2);
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	node->cmd[0] = ft_strdup(curr->next->value);
	node->cmd[1] = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->left = build_execution_tree(start, curr);
	node->right = NULL;
	return (node);
}

// Modified to handle multiple redirections properly
t_exec_node	*find_and_create_redirect_node(t_token *start, t_token *end)
{
	t_token *last_in_redir;
	t_token *last_out_redir;
	t_token *last_append_redir;
	t_token *rightmost_redir;

	// Find the last redirection of each type
	last_in_redir = find_last_redirection(start, end, TOKEN_REDIR_IN);
	last_out_redir = find_last_redirection(start, end, TOKEN_REDIR_OUT);
	last_append_redir = find_last_redirection(start, end, TOKEN_APPEND);

	// Find the rightmost redirection overall
	rightmost_redir = NULL;
	if (last_in_redir)
		rightmost_redir = last_in_redir;
	if (last_out_redir && (!rightmost_redir || last_out_redir > rightmost_redir))
		rightmost_redir = last_out_redir;
	if (last_append_redir && (!rightmost_redir || last_append_redir > rightmost_redir))
		rightmost_redir = last_append_redir;

	if (rightmost_redir)
		return (create_redirect_node(start, rightmost_redir, end));

	return (NULL);
}