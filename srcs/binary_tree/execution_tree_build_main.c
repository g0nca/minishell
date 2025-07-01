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
    t_exec_node	*redir_node;
	(void)shell; // shell is not used in this function, but kept for consistency

    cmd_node = create_command_node(start, end);
    if (!cmd_node)
        return (NULL);

    curr = start;
    while (curr && curr != end)
    {
        if (is_redirection(curr->type) && curr->next && curr->next->type == TOKEN_WORD)
        {
            redir_node = malloc(sizeof(t_exec_node));
            if (!redir_node)
            {
                free_execution_tree(cmd_node);
                return (NULL);
            }
            redir_node->type = get_redirect_node_type(curr->type);
            redir_node->cmd = malloc(sizeof(char *) * 2);
            if (!redir_node->cmd)
            {
                free(redir_node);
                free_execution_tree(cmd_node);
                return (NULL);
            }
            redir_node->cmd[0] = ft_strdup(curr->next->value);
            redir_node->cmd[1] = NULL;
            redir_node->fd_in = -1;
            redir_node->fd_out = -1;
            redir_node->left = cmd_node;
            redir_node->right = NULL;
            cmd_node = redir_node;
            curr = curr->next; // skip filename
        }
        curr = curr->next;
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
