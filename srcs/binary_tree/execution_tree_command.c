/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:55:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:00:51 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_file_descriptors(t_exec_node *node)
{
	if (node->fd_in != -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
		node->fd_in = -1;
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
		node->fd_out = -1;
	}
}

void	execute_command_node(t_exec_node *node, t_shell *shell)
{
	int		stdin_backup;
	int		stdout_backup;
	t_token	*cmd_token;

	if (!node || !node->cmd || !node->cmd[0])
		return ;
	cmd_token = create_token_chain(node->cmd);
	stdin_backup = -1;
	stdout_backup = -1;
	if (node->fd_in != -1 || node->fd_out != -1)
		ft_backup_stdio(&stdin_backup, &stdout_backup);
	setup_file_descriptors(node);
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
	if (stdin_backup != -1 || stdout_backup != -1)
		ft_restore_stdio(stdin_backup, stdout_backup);
}

void	execute_tree(t_exec_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		execute_command_tree(node, shell);
	else if (node->type == NODE_PIPE)
		execute_pipe_node(node, shell);
}

void	setup_redirections(t_shell *shell)
{
	int	fd;

	if (shell->in)
	{
		fd = open(shell->in, O_RDONLY);
		if (fd == -1)
			shell_error(shell, "Open file error\n", 50, EXIT_FAILURE);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (shell->out)
	{
		if (shell->append)
			fd = open(shell->out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(shell->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fd = open(shell->out, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			shell_error(shell, "Open file error\n", 50, EXIT_FAILURE);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
