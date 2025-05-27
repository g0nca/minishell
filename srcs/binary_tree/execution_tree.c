/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:39:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/27 13:44:13 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_exec *build_execution_tree_safe(t_token *token_list)
{
    t_token *curr = token_list;
    t_token *first_pipe = NULL;
    
    // Find first pipe
    while (curr)
    {
        if (curr->type == TOKEN_PIPE)
        {
            first_pipe = curr;
            break;
        }
        curr = curr->next;
    }
    
    if (first_pipe)
    {
        // Copy segments without modifying original
        t_token *left_tokens = copy_token_segment(token_list, first_pipe->prev);
        t_token *right_tokens = copy_token_segment(first_pipe->next, get_last_token(token_list));
        
        t_exec *node = create_node(NODE_PIPE, NULL);
        node->left = build_execution_tree_safe(left_tokens);
        node->right = build_execution_tree_safe(right_tokens);
        
        return (node);
    }
    else
    {
        // Copy the entire segment for this command
        t_token *cmd_tokens = copy_token_segment(token_list, get_last_token(token_list));
        return create_node(NODE_COMMAND, cmd_tokens);
    }
}

t_token *copy_token_segment(t_token *start, t_token *end)
{
    if (!start)
        return (NULL);
    
    t_token *new_head = NULL;
    t_token *new_tail = NULL;
    t_token *curr = start;
    
    // Copy tokens from start to end (inclusive)
    while (curr)
    {
        // Create new token
        t_token *new_token = malloc(sizeof(t_token));
        if (!new_token)
        {
            // Free already allocated tokens on failure
            free_token_list(new_head);
            return (NULL);
        }
        
        // Copy token data
        new_token->type = curr->type;
        new_token->value = strdup(curr->value); // Duplicate the string
        if (!new_token->value)
        {
            free(new_token);
            free_token_list(new_head);
            return (NULL);
        }
        
        new_token->next = NULL;
        new_token->prev = NULL;
        
        // Link to the new chain
        if (!new_head)
        {
            new_head = new_token;
            new_tail = new_token;
        }
        else
        {
            new_tail->next = new_token;
            new_token->prev = new_tail;
            new_tail = new_token;
        }
        
        // Stop if we reached the end token
        if (curr == end)
            break;
            
        curr = curr->next;
    }
    
    return (new_head);
}

// Helper function to free a token list (for cleanup)
void free_token_list(t_token *tokens)
{
    t_token *curr = tokens;
    t_token *next;
    
    while (curr)
    {
        next = curr->next;
        if (curr->value)
            free(curr->value);
        free(curr);
        curr = next;
    }
}
// Helper function to get the last token in a chain
t_token *get_last_token(t_token *tokens)
{
    if (!tokens)
        return (NULL);
    
    while (tokens->next)
        tokens = tokens->next;
    
    return (tokens);
}

// Example of how the tree should look for: cmd1 | cmd2 | cmd3
/*
Tree structure:
        PIPE
       /    \
    PIPE    cmd3
   /    \
 cmd1  cmd2

This ensures left-associative execution: (cmd1 | cmd2) | cmd3
*/

t_exec	*create_node(t_exec_type type, t_token *token)
{
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
	node->type = type;
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}


