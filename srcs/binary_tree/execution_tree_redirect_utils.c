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

t_exec_node	*create_redirect_node(t_token *start, t_token *curr, t_token *end)
{
    t_exec_node	*node;

    node = malloc(sizeof(t_exec_node));
    if (!node)
        return (NULL);
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
    node->left = build_execution_tree_skip_redirect(start, curr, end);
    node->right = NULL;
    return (node);
}

t_exec_node *build_execution_tree_skip_redirect(t_token *start, t_token *redirect, t_token *end)
{
    t_token *current;
    t_exec_node *node;
    t_token *filtered_start;
    t_token *filtered_end;

    current = start;
    node = NULL;
    filtered_start = NULL;
    filtered_end = NULL;
    while (current && current != end)
    {
        if (current == redirect)
        {
            current = current->next;
            if (current && current != end)
                current = current->next;
            continue;
        }
        if (!filtered_start)
            filtered_start = current;
        current = current->next;
    }
    filtered_end = end;
    node = create_command_node(filtered_start, filtered_end);
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
