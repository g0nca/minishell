/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:08:43 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:10:18 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_output_redirect(t_exec_node *node, t_shell *shell)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (node->type == NODE_REDIRECT_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(node->cmd[0], flags, 0644);
	if (fd < 0)
	{
		perror("open");
		shell->last_exit_status = 1;
		return ;
	}
	if (node->left)
	{
		node->left->fd_out = fd;
		execute_tree(node->left, shell);
	}
	else
		close(fd);
}

void	execute_input_redirect(t_exec_node *node, t_shell *shell)
{
	int	fd;

	//ft_printf_fd(1, "CMD:%s\n", node->cmd[0]);
	fd = open(node->cmd[0], O_RDONLY);
	//ft_printf_fd(1, "FD: %d\n", fd);
	if (fd < 0)
	{
		perror("open");
		shell->last_exit_status = 1;
		return ;
	}
	if (node->left)
	{
		node->left->fd_in = fd;
		execute_tree(node->left, shell);
	}
	else
		close(fd);
}
