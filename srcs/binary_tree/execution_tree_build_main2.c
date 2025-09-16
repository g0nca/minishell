/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:49:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 10:51:38 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	open_input_file(t_exec_node *cmd, char *filename)
{
	cmd->fd_in = open(filename, O_RDONLY);
	if (cmd->fd_in < 0)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}

static int	open_output_file(t_exec_node *cmd, char *filename, int append)
{
	int	flags;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->fd_out = open(filename, flags, 0644);
	if (cmd->fd_out < 0)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}

static int	apply_redirects(t_exec_node *cmd, char *in, char *out, char *append)
{
	if (in && open_input_file(cmd, in) < 0)
		return (-1);
	if (out && open_output_file(cmd, out, 0) < 0)
		return (-1);
	if (append && open_output_file(cmd, append, 1) < 0)
		return (-1);
	return (0);
}

static int	process_redirects(t_token *start,
	t_token *end, t_shell *shell, t_redirs *redirs)
{
	t_token	*curr;

	curr = start;
	while (curr && curr != end)
	{
		if (curr->type == TOKEN_HERE_DOC
			&& curr->next && curr->next->type == TOKEN_WORD)
		{
			redirs->in = create_heredoc(curr->next->value, shell);
			if (!redirs->in)
				return (-1);
		}
		else if (curr->type == TOKEN_REDIR_IN
			&& curr->next && curr->next->type == TOKEN_WORD)
			redirs->in = curr->next->value;
		else if (curr->type == TOKEN_REDIR_OUT
			&& curr->next && curr->next->type == TOKEN_WORD)
			redirs->out = curr->next->value;
		else if (curr->type == TOKEN_APPEND
			&& curr->next && curr->next->type == TOKEN_WORD)
			redirs->append = curr->next->value;
		curr = curr->next;
	}
	return (0);
}

t_exec_node	*wrap_with_redirects(t_token *start, t_token *end, t_shell *shell)
{
	t_exec_node	*cmd;
	t_redirs	redirs;

	ft_bzero(&redirs, sizeof(redirs));
	cmd = create_command_node(start, end);
	if (!cmd)
		return (NULL);
	if (process_redirects(start, end, shell, &redirs) < 0)
	{
		shell->last_exit_status = 1;
		return (free_execution_tree(cmd), NULL);
	}
	if (apply_redirects(cmd, redirs.in, redirs.out, redirs.append) < 0)
	{
		shell->last_exit_status = 1;
		return (free_execution_tree(cmd), NULL);
	}
	return (cmd);
}
