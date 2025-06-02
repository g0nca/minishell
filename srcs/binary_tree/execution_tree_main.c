/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:01:13 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/06/02 11:24:04 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_child_process(t_exec_node *node, t_shell *shell)
{
	execute_tree(node, shell);
	exit(shell->last_exit_status);
}

void	handle_parent_process(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (manual_wifexited(status))
		shell->last_exit_status = manual_wexitstatus(status);
	else
		shell->last_exit_status = 1;
}
int		is_simple_builtin_command(t_exec_node *node)
{
	return (node->type == NODE_COMMAND && node->cmd && node->cmd[0] && is_builtin(node->cmd[0]) && node->fd_in == -1 && node->fd_out == -1);
}
void	execute_command_tree(t_exec_node *node, t_shell *shell)
{
	pid_t	pid;
	t_token	*cmd_token;

	if (!node)
		return ;
	if (is_simple_builtin_command(node))
	{
		cmd_token = create_token_chain(node->cmd);
		if (cmd_token)
		{
			run_builtin(cmd_token, shell);
			free_tokens(&cmd_token);
		}
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		shell->last_exit_status = 1;
		return ;
	}
	if (pid == 0)
		handle_child_process(node, shell);
	else
		handle_parent_process(pid, shell);
}
