/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:03:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:05:18 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_pipe_left_child(int *pipe_fd, t_exec_node *node,
			t_shell *shell)
{
	if (!node || !node->left)
		return ;
	close(pipe_fd[0]);
	if (node->left->fd_out == -1)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else
		dup2(node->left->fd_out, STDOUT_FILENO);
	close(pipe_fd[1]);
	execute_tree(node->left, shell);
	//exit(shell->last_exit_status);
}

void	setup_pipe_right_child(int *pipe_fd, t_exec_node *node, t_shell *shell)
{
	if (!node || !node->right)
		return ;
	close(pipe_fd[1]);
	if (node->right->fd_in == -1)
		dup2(pipe_fd[0], STDIN_FILENO);
	else
		dup2(node->right->fd_in, STDIN_FILENO);
	close(pipe_fd[0]);
	execute_tree(node->right, shell);
	//exit(shell->last_exit_status);
}

void	handle_pipe_parent(int *pipe_fd, pid_t left_pid,
		pid_t right_pid, t_shell *shell)
{
	int	status;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
	if (my_wifexited(status))
		shell->last_exit_status = manual_wexitstatus(status);
	else
		shell->last_exit_status = 1;
}
