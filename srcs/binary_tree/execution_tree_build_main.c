/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:49:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/09 09:54:46 by ggomes-v         ###   ########.fr       */
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

void	free_execution_tree(t_exec_node *node, int flag)
{
	if (!node)
		return ;
	if (flag == 0)
	{
		free_cmd(node->cmd);
		free(node);
		return ;
	}
	if (node->left)
		free_execution_tree(node->left, 1);
	if (node->right)
		free_execution_tree(node->right, 1);
	free_cmd(node->cmd);
	if (node->heredoc != NULL)
	{
		free(node->heredoc);
		node->heredoc = NULL;
	}
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->fd_out != -1)
		close(node->fd_out);
	free(node);
}
