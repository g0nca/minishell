/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:51:54 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 10:55:28 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Helper function to process all redirections in token order
int	process_token_redirections(t_token *start, t_token *end, t_shell *shell)
{
    (void)shell;
	t_token *curr;
	int fd;
	int flags;

	curr = start;
	while (curr && curr != end && curr->next)
	{
		if (curr->type == TOKEN_REDIR_IN && curr->next->type == TOKEN_WORD)
		{
			fd = open(curr->next->value, O_RDONLY);
			if (fd < 0)
			{
				ft_printf_fd(2, "minishell: %s: No such file or directory\n", curr->next->value);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if ((curr->type == TOKEN_REDIR_OUT || curr->type == TOKEN_APPEND) 
				&& curr->next->type == TOKEN_WORD)
		{
			flags = O_WRONLY | O_CREAT;
			if (curr->type == TOKEN_APPEND)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;
				
			fd = open(curr->next->value, flags, 0644);
			if (fd < 0)
			{
				ft_printf_fd(2, "minishell: %s: ", curr->next->value);
				perror("");
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		curr = curr->next;
	}
	return (0);
}

t_token	*find_last_pipe(t_token *start, t_token *end)
{
	t_token		*curr;
	t_token		*last_pipe;

	curr = start;
	last_pipe = NULL;
	while (curr && curr != end)
	{
		if (curr->type == TOKEN_PIPE)
			last_pipe = curr;
		curr = curr->next;
	}
	return (last_pipe);
}

t_exec_node	*create_pipe_node(t_token *start, t_token *last_pipe, t_token *end)
{
	t_exec_node	*node;

	node = malloc(sizeof(t_exec_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->cmd = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->left = build_execution_tree(start, last_pipe);
	node->right = build_execution_tree(last_pipe->next, end);
	return (node);
}

t_node_type	get_redirect_node_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (NODE_REDIRECT_IN);
	else if (type == TOKEN_REDIR_OUT)
		return (NODE_REDIRECT_OUT);
	else
		return (NODE_REDIRECT_APPEND);
}

// Modified create_command_node to handle redirections inline
t_exec_node *create_command_node(t_token *start, t_token *end)
{
    t_exec_node *node;
    t_token *current;
    int arg_count;
    int i;

    if (!start)
        return (NULL);

    node = malloc(sizeof(t_exec_node));
    if (!node)
        return (NULL);

    node->type = NODE_COMMAND;
    node->left = NULL;
    node->right = NULL;
    node->fd_in = -1;
    node->fd_out = -1;
    node->original_start = start;
    node->original_end = end;

    // Store original token range for redirection processing
    node->cmd = NULL; // Will be set by token processing function

    // Count arguments (excluding redirections)
    arg_count = 0;
    current = start;
    while (current && current != end)
    {
        if (current->type == TOKEN_CMD || current->type == TOKEN_WORD)
        {
            arg_count++;
            current = current->next;
        }
        else if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
            || current->type == TOKEN_APPEND || current->type == TOKEN_HERE_DOC)
        {
            // Skip redirection operator
            current = current->next;
            // Skip filename
            if (current && current != end && current->type == TOKEN_WORD)
                current = current->next;
        }
        else if (current->type == TOKEN_PIPE)
        {
            break;
        }
        else
        {
            current = current->next;
        }
    }

    if (arg_count == 0)
    {
        free(node);
        return (NULL);
    }

    // Allocate cmd array
    node->cmd = malloc(sizeof(char *) * (arg_count + 1));
    if (!node->cmd)
    {
        free(node);
        return (NULL);
    }

    // Fill cmd array with arguments (excluding redirections)
    i = 0;
    current = start;
    while (current && current != end && i < arg_count)
    {
        if (current->type == TOKEN_CMD || current->type == TOKEN_WORD)
        {
            node->cmd[i] = ft_strdup(current->value);
            if (!node->cmd[i])
            {
                // Cleanup on error
                while (--i >= 0)
                    free(node->cmd[i]);
                free(node->cmd);
                free(node);
                return (NULL);
            }
            i++;
            current = current->next;
        }
        else if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
            || current->type == TOKEN_APPEND || current->type == TOKEN_HERE_DOC)
        {
            // Skip redirection operator
            current = current->next;
            // Skip filename
            if (current && current != end && current->type == TOKEN_WORD)
                current = current->next;
        }
        else if (current->type == TOKEN_PIPE)
        {
            break;
        }
        else
        {
            current = current->next;
        }
    }
    node->cmd[i] = NULL;

    return (node);
}