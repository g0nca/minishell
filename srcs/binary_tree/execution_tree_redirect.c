/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:08:43 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:10:18 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Process ALL input redirections in order (bash behavior)
int	process_all_input_redirections(t_token *start, t_token *end, t_shell *shell)
{
	t_token *curr;
	int fd;
	int last_valid_fd = -1;

	curr = start;
	while (curr && curr != end && curr->next)
	{
		if (curr->type == TOKEN_REDIR_IN && curr->next->type == TOKEN_WORD)
		{
			fd = open(curr->next->value, O_RDONLY);
			if (fd < 0)
			{
				ft_printf_fd(2, "minishell: %s: No such file or directory\n", curr->next->value);
				shell->last_exit_status = 1;
				if (last_valid_fd != -1)
					close(last_valid_fd);
				return (-1);
			}
			// Close previous fd if we had one
			if (last_valid_fd != -1)
				close(last_valid_fd);
			last_valid_fd = fd;
		}
		curr = curr->next;
	}
	return (last_valid_fd);
}

// Process ALL output redirections in order (bash behavior)
int	process_all_output_redirections(t_token *start, t_token *end, t_shell *shell)
{
	t_token *curr;
	int fd;
	int last_valid_fd = -1;
	int flags;

	curr = start;
	while (curr && curr != end && curr->next)
	{
		if ((curr->type == TOKEN_REDIR_OUT || curr->type == TOKEN_APPEND) 
			&& curr->next->type == TOKEN_WORD)
		{
			flags = O_WRONLY | O_CREAT;
			if (curr->type == TOKEN_APPEND)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;
				
			fd = open(curr->next->value, flags, 0644);
			if (fd < 0)
			{
				ft_printf_fd(2, "minishell: %s: ", curr->next->value);
				perror("");
				shell->last_exit_status = 1;
				if (last_valid_fd != -1)
					close(last_valid_fd);
				return (-1);
			}
			// Close previous fd if we had one
			if (last_valid_fd != -1)
				close(last_valid_fd);
			last_valid_fd = fd;
		}
		curr = curr->next;
	}
	return (last_valid_fd);
}

void	execute_output_redirect(t_exec_node *node, t_shell *shell)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (node->type == NODE_REDIRECT_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(node->cmd[0], flags, 0644);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: %s: ", node->cmd[0]);
		perror("");
		shell->last_exit_status = 1;
		return ;
	}
	if (node->left)
	{
		node->left->fd_out = fd;
		execute_tree(node->left, shell);
	}
	else
		close(fd);
}

void	execute_input_redirect(t_exec_node *node, t_shell *shell)
{
	int	fd;

	fd = open(node->cmd[0], O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n", node->cmd[0]);
		shell->last_exit_status = 1;
		return ;
	}
	if (node->left)
	{
		node->left->fd_in = fd;
		execute_tree(node->left, shell);
	}
	else
		close(fd);
}