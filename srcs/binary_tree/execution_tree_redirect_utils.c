/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_redirect_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:10:37 by ggomes-v          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/30 11:01:33 by ggomes-v         ###   ########.fr       */
=======
/*   Updated: 2025/05/29 11:12:23 by ggomes-v         ###   ########.fr       */
>>>>>>> PIPES
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT || type == TOKEN_APPEND);
}
<<<<<<< HEAD
=======

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
	node->cmd[0] = strdup(curr->next->value);
	node->cmd[1] = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->left = build_execution_tree(start, curr);
	node->right = NULL;
	return (node);
}

t_exec_node	*find_and_create_redirect_node(t_token *start, t_token *end)
{
	t_token	*curr;

	curr = start;
	while (curr && curr != end && curr->next)
	{
		if (is_redirection(curr->type) && curr->next->type == TOKEN_WORD)
			return (create_redirect_node(start, curr, end));
		curr = curr->next;
	}
	return (NULL);
}
>>>>>>> PIPES
