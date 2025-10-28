/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:55:48 by ggomes-v          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/09 10:49:42 by ggomes-v         ###   ########.fr       */
=======
/*   Updated: 2025/05/29 11:00:51 by ggomes-v         ###   ########.fr       */
>>>>>>> PIPES
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

<<<<<<< HEAD
=======
void	setup_file_descriptors(t_exec_node *node)
{
	if (node->fd_in != -1)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
}

t_token	*create_token_chain(char **cmd)
{
	t_token	*cmd_token;
	t_token	*current;
	t_token	*arg_token;
	int		i;

	cmd_token = create_token(cmd[0], TOKEN_CMD);
	if (!cmd_token)
		return (NULL);
	current = cmd_token;
	i = 1;
	while (cmd[i])
	{
		arg_token = create_token(cmd[i], TOKEN_WORD);
		if (!arg_token)
		{
			free_tokens(&cmd_token);
			return (NULL);
		}
		current->next = arg_token;
		arg_token->prev = current;
		current = arg_token;
		i++;
	}
	return (cmd_token);
}

>>>>>>> PIPES
void	execute_command_node(t_exec_node *node, t_shell *shell)
{
	t_token	*cmd_token;

<<<<<<< HEAD
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
=======
	setup_file_descriptors(node);
	if (node->cmd && node->cmd[0])
	{
		cmd_token = create_token_chain(node->cmd);
		if (!cmd_token)
			exit(EXIT_FAILURE);
		execute_command(cmd_token, shell);
		free_tokens(&cmd_token);
	}
>>>>>>> PIPES
}

void	execute_tree(t_exec_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
<<<<<<< HEAD
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
=======
		execute_command_node(node, shell);
	else if (node->type == NODE_PIPE)
		execute_pipe_node(node, shell);
	else if (node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_REDIRECT_APPEND)
		execute_output_redirect(node, shell);
	else if (node->type == NODE_REDIRECT_IN)
		execute_input_redirect(node, shell);
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
>>>>>>> PIPES
}
