/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:01:13 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/28 12:42:20 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_process(t_exec_node *node, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	setup_redirections(shell, node);
	execute_command_node(node, shell);
	free_execution_tree(shell->tree, 1);
	free_tokens(&shell->token);
	free(shell->token);
	free_struct(shell, 1);
	g_exit_status = shell->last_exit_status;
	free(shell);
	exit(g_exit_status);
}

static void	parent_process(pid_t pid, t_shell *shell)
{
	int		status;
	void	(*prev_sigint)(int);

	prev_sigint = signal(SIGINT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, prev_sigint);
	if (my_wifsignaled(status))
	{
		if (my_wtermsig(status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			shell->last_exit_status = 130;
		}
		else if (my_wtermsig(status) == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			shell->last_exit_status = 131;
		}
	}
	else
		shell->last_exit_status = manual_wexitstatus(status);
}

static void	execute_builtin_with_redirects(t_exec_node *node, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (setup_redirections(shell, node) != 0)
	{
		shell->last_exit_status = 1;
		close(stdin_backup);
		close(stdout_backup);
		return ;
	}
	execute_command_node(node, shell);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

static void	execute_external_command(t_exec_node *node, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_process(node, shell);
	else if (pid > 0)
		parent_process(pid, shell);
}

void	execute_command_tree(t_exec_node *node, t_shell *shell)
{
	if (is_builtin(node->cmd[0]))
		execute_builtin_with_redirects(node, shell);
	else if (node->cmd != NULL)
		execute_external_command(node, shell);
}
