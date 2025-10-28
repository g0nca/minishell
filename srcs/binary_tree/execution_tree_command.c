/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:55:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/09 10:49:42 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_command_node(t_exec_node *node, t_shell *shell)
{
	t_token	*cmd_token;

	if (!node || !node->cmd || !node->cmd[0])
		return ;
	cmd_token = create_token_chain(node->cmd);
	if (is_builtin(node->cmd[0]))
	{
		if (cmd_token)
		{
			run_builtin(cmd_token, shell);
			free_tokens(&cmd_token);
		}
	}
	else
		handle_env_path_execution(node->cmd, shell);
	free_tokens(&cmd_token);
}

void	execute_tree(t_exec_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		execute_command_tree(node, shell);
	else if (node->type == NODE_PIPE)
		execute_pipe_node(node, shell);
	if (node->heredoc)
		unlink(node->heredoc);
}

static int	setup_redirections_input(t_shell *shell, t_exec_node *node)
{
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->last_redir_in_type == 6)
		node->fd_in = open(node->heredoc, O_RDONLY);
	else if (node->last_redir_in_type == 3)
		node->fd_in = open(node->last_redir_in, O_RDONLY);
	if (node->fd_in == -1)
	{
		shell_error(shell, "Open file error\n", 50, EXIT_FAILURE);
		return (-1);
	}
	dup2(node->fd_in, STDIN_FILENO);
	close(node->fd_in);
	return (0);
}

static int	setup_redirections_output(t_shell *shell, t_exec_node *node)
{
	if (node->append_file)
	{
		node->fd_out = open(node->append_file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	}
	else
	{
		node->fd_out = open(node->output_file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	}
	if (node->fd_out == -1)
	{
		shell_error(shell, "Open file error\n", 50, EXIT_SUCCESS);
		return (-1);
	}
	dup2(node->fd_out, STDOUT_FILENO);
	close(node->fd_out);
	return (0);
}

int	setup_redirections(t_shell *shell, t_exec_node *node)
{
	if (node->input_file || node->heredoc)
	{
		if (setup_redirections_input(shell, node) != 0)
			return (-1);
	}
	if (node->output_file || node->append_file)
	{
		if (setup_redirections_output(shell, node) != 0)
			return (-1);
	}
	return (0);
}
