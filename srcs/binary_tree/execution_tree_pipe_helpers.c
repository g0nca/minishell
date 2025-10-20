/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_pipe_helpers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:05:36 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:08:27 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_pipe_and_check(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

pid_t	fork_left_child(int *pipe_fd, t_exec_node *node, t_shell *shell)
{
	pid_t	left_pid;

	if (!node->left)
		return (0);
	ft_printf_fd(STDOUT_FILENO, "\033[1;31mFORK_LEFT_CHILD\033[0m\n");
	left_pid = fork();
	if (left_pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (left_pid == 0)
	{
		setup_pipe_left_child(pipe_fd, node, shell);
		free_execution_tree(node);
		free_tokens(&shell->token);
		free(shell->token);
		g_exit_status = shell->last_exit_status;
		free_struct(shell, 1);
		exit(g_exit_status);
	}
	return (left_pid);
}

pid_t	fork_right_child(int *pipe_fd, t_exec_node *node,
		t_shell *shell, pid_t left_pid)
{
	pid_t	right_pid;

	if (!node->right)
		return (0);
	ft_printf_fd(STDOUT_FILENO, "\033[1;31mFORK_RIGHT_CHILD\033[0m\n");
	right_pid = fork();
	if (right_pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(left_pid, NULL, 0);
		return (-1);
	}
	if (right_pid == 0)
	{
		setup_pipe_right_child(pipe_fd, node, shell);
		free_execution_tree(node);
		free_tokens(&shell->token);
		free(shell->token);
		g_exit_status = shell->last_exit_status;
		free_struct(shell, 1);
		exit(g_exit_status);
	}
	return (right_pid);
}

void	execute_pipe_node(t_exec_node *node, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (create_pipe_and_check(pipe_fd) == -1)
		return ;
	left_pid = fork_left_child(pipe_fd, node, shell);
	if (left_pid == -1)
		return ;
	right_pid = fork_right_child(pipe_fd, node, shell, left_pid);
	if (right_pid == -1)
		return ;
	handle_pipe_parent(pipe_fd, left_pid, right_pid, shell);
}
