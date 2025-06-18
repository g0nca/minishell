/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:01:13 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/06/17 10:21:21 by andrade          ###   ########.fr       */
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
    pid_t pid;

    pid = 0;
    if (is_builtin(node->cmd[0]))
        execute_command_node(node, shell); // Builtin: executa no processo principal
    else
    {
        pid = fork();
        if (pid == 0)
        {
            execute_command_node(node, shell); // Externo: executa no filho
            exit(shell->last_exit_status);
        }
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
            shell->last_exit_status = WEXITSTATUS(status);
        }
    }
}
