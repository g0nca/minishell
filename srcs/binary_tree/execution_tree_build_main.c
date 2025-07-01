/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:49:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 10:51:38 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_exec_node	*wrap_with_redirects(t_token *start, t_token *end, t_shell *shell)
{
    t_token		*curr;
    t_exec_node	*cmd_node;
    char        *last_in = NULL;
    char        *last_out = NULL;
    char        *last_append = NULL;

    (void)shell;

    cmd_node = create_command_node(start, end);
    if (!cmd_node)
        return (NULL);

    curr = start;
    while (curr && curr != end)
    {
        if (curr->type == TOKEN_REDIR_IN && curr->next && curr->next->type == TOKEN_WORD)
            last_in = curr->next->value;
        else if (curr->type == TOKEN_REDIR_OUT && curr->next && curr->next->type == TOKEN_WORD)
            last_out = curr->next->value;
        else if (curr->type == TOKEN_APPEND && curr->next && curr->next->type == TOKEN_WORD)
            last_append = curr->next->value;
        curr = curr->next;
    }

    // Open the last input file if any
    if (last_in)
    {
        cmd_node->fd_in = open(last_in, O_RDONLY);
        if (cmd_node->fd_in < 0)
        {
            free_execution_tree(cmd_node);
            return (NULL);
        }
    }
    // Open the last output file (append has priority if both exist)
    if (last_append)
    {
        cmd_node->fd_out = open(last_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (cmd_node->fd_out < 0)
        {
            free_execution_tree(cmd_node);
            return (NULL);
        }
    }
    else if (last_out)
    {
        cmd_node->fd_out = open(last_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (cmd_node->fd_out < 0)
        {
            free_execution_tree(cmd_node);
            return (NULL);
        }
    }
    return cmd_node;
}

t_exec_node	*build_execution_tree(t_token *start, t_token *end, t_shell *shell)
{
    t_token		*last_pipe;

    if (!start || start == end)
        return (NULL);
    last_pipe = find_last_pipe(start, end);
    if (last_pipe)
        return (create_pipe_node(start, last_pipe, end, shell));
    // Instead of find_and_create_redirect_node, use the new wrapper
    return (wrap_with_redirects(start, end, shell));
}

void	free_execution_tree(t_exec_node *node)
{
	if (!node)
		return ;
	free_execution_tree(node->left);
	free_execution_tree(node->right);
	free_cmd(node->cmd);
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->fd_out != -1)
		close(node->fd_out);
	free(node);
}
