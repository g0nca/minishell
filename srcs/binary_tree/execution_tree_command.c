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
	}
	if (node->fd_out != -1)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
}

// Process ALL redirections from the original token list
int	setup_command_redirections(t_token *start, t_token *end, t_shell *shell)
{
	int input_fd;
	int output_fd;

	// Process all input redirections
	input_fd = process_token_redirections(start, end, shell);
	if (input_fd == -1 && shell->last_exit_status != 0)
		return (-1);

	// Process all output redirections
	output_fd = process_token_redirections(start, end, shell);
	if (output_fd == -1 && shell->last_exit_status != 0)
	{
		if (input_fd != -1)
			close(input_fd);
		return (-1);
	}

	// Apply the final redirections
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != -1)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}

	return (0);
}

// Create a token chain from cmd array, but preserve all arguments
t_token	*create_token_chain(char **cmd)
{
	t_token	*cmd_token;
	t_token	*current;
	t_token	*arg_token;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
		
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

void	execute_command_node(t_exec_node *node, t_shell *shell)
{
	if (!node || !node->cmd || !node->cmd[0])
		return;

	// Process ALL redirections from original token list
	if (process_token_redirections(node->original_start, node->original_end, shell) != 0)
		return;

	setup_file_descriptors(node);
	
	if (is_builtin(node->cmd[0]))
	{
		t_token	*cmd_token = create_token_chain(node->cmd);
		if (cmd_token)
		{
			run_builtin(cmd_token, shell);
			free_tokens(&cmd_token);
		}
	}
	else
	{
		handle_env_path_execution(node->cmd, shell);
	}
}

void	execute_tree(t_exec_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
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
}