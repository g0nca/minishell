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

static int	open_input_file(t_exec_node *cmd, char *filename, t_shell *shell)
{
	cmd->fd_in = open(filename, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		shell_error(shell, filename, 2, EXIT_SUCCESS);
		return (-1);
	}
	return (0);
}

static int  open_output_file(t_exec_node *cmd, char *filename,
        int append, t_shell *shell)
{
    static int  error_reported;

	error_reported = 0;
	if (append == 1)
        cmd->fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        cmd->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fd_out == -1)
    {
        if (!error_reported)
        {
            shell_error(shell, filename, 3, EXIT_SUCCESS);
            error_reported = 1;
        }
        return (-1);
    }
    return (0);
}

static int	process_redirects(t_token *start, 
		t_exec_node	*cmd, t_shell *shell, t_redirs *redirs)
{
	t_token	*curr;

	curr = start;
	while (curr && curr != NULL)
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
		{
			redirs->in = curr->next->value;
			curr = curr->next;
			if (open_input_file(cmd, curr->value, shell) < 0)
				return (-1);
		}
		else if (curr->type == TOKEN_REDIR_OUT
			&& curr->next && curr->next->type == TOKEN_WORD)
		{
			redirs->out = curr->next->value;
			curr = curr->next;
			if (open_output_file(cmd, curr->value, false, shell) < 0)
				return (-1);
		}
		else if (curr->type == TOKEN_APPEND
			&& curr->next && curr->next->type == TOKEN_WORD)
		{
			redirs->append = curr->next->value;
			curr = curr->next;
			if (open_output_file(cmd, curr->value, true, shell) < 0)
				return (-1);
		}
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
	if (process_redirects(start, cmd, shell, &redirs) < 0)
	{
		shell->last_exit_status = 1;
		return (free_execution_tree(cmd), NULL);
	}
	/*if (apply_redirects(cmd, &redirs) < 0)
	{
		shell->last_exit_status = 1;
		return (free_execution_tree(cmd), NULL);
	}*/
	return (cmd);
}