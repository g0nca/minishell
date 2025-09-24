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

t_exec_node	*build_execution_tree(t_token *start, t_token *end, t_shell *shell)
{
	t_token		*last_pipe;

	if (!start || start == end)
		return (NULL);
	last_pipe = find_last_pipe(start, end);
	if (last_pipe)
		return (create_pipe_node(start, last_pipe, end, shell));
	return (wrap_with_redirects(start, end, shell));
}

void cleanup_exec_node(t_exec_node *node)
{
    if (!node)
        return;
        
    // Fecha FDs se ainda estão abertos
    if (node->fd_in != -1)
    {
        close(node->fd_in);
        node->fd_in = -1;
    }
    if (node->fd_out != -1)
    {
        close(node->fd_out);
        node->fd_out = -1;
    }
    
    // Recursivamente limpa nós filhos
    if (node->left)
        cleanup_exec_node(node->left);
    if (node->right)
        cleanup_exec_node(node->right);
}

void	free_execution_tree(t_exec_node *node)
{
	if (!node)
		return ;
	cleanup_exec_node(node);
	free_execution_tree(node->left);
	free_execution_tree(node->right);
	free_cmd(node->cmd);
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->fd_out != -1)
		close(node->fd_out);
	free(node);
}
