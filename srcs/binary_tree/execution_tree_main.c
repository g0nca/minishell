/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:01:13 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/07/07 11:10:16 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_process(t_exec_node *node, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (node->fd_in == -1)
		dup2(STDIN_FILENO, 0);
	if (node->fd_out == -1)
		dup2(STDOUT_FILENO, 1);
	execute_command_node(node, shell);
	exit(shell->last_exit_status);
}

static void	parent_process(pid_t pid, t_shell *shell)
{
	int		status;
	void	(*prev_sigint)(int);

	prev_sigint = signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, prev_sigint);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
	shell->last_exit_status = WEXITSTATUS(status);
}

void	execute_command_tree(t_exec_node *node, t_shell *shell)
{
	pid_t	pid;

	if (is_builtin(node->cmd[0]))
		execute_command_node(node, shell);
	else
	{
		pid = fork();
		if (pid == 0)
			child_process(node, shell);
		else if (pid > 0)
			parent_process(pid, shell);
	}
}
