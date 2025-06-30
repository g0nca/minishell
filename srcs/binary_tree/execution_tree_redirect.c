/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:08:43 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/06/30 11:09:28 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_output_redirect(t_exec_node *node, t_shell *shell)
{
	int	fd;

	if (node->type == NODE_REDIRECT_APPEND)
		fd = open(node->cmd[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(node->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		shell->last_exit_status = 1;
		return ;
	}
	if (node->left)
	{
		node->left->fd_out = fd;
		execute_tree(node->left, shell);
	}
	else if (node->right)
	{
		node->right->fd_out = fd;
		execute_tree(node->right, shell);
	}
	else
		close(fd);
}

void	execute_input_redirect(t_exec_node *node, t_shell *shell)
{
	int	fd;

	fd = open(node->cmd[0], O_RDONLY);
	if (fd < 0)
	{
		shell_error(shell, node->cmd[0], 2, false);
		shell->last_exit_status = 1;
		return ;
	}
	if (node->left)
	{
		node->left->fd_in = fd;
		execute_tree(node->left, shell);
	}
	else if (node->right)
	{
		node->right->fd_in = fd;
		execute_tree(node->right, shell);
	}
	else
		close(fd);
}
