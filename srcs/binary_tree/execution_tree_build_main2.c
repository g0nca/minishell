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

int	open_input_file(t_exec_node *cmd, char *filename, t_shell *shell)
{
	(void)cmd;
	if (access(filename, F_OK | R_OK) == -1)
	{
		shell_error(shell, filename, 15, EXIT_SUCCESS);
		return (-1);
	}
	return (0);
}

int	open_output_file(t_exec_node *cmd, char *filename,
		int append, t_shell *shell)
{
	(void)shell;
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	if (append == 1)
		cmd->fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		cmd->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
	{
		shell_error(shell, filename, 3, EXIT_SUCCESS);
		return (-1);
	}
	close(cmd->fd_out);
	return (0);
}

static int	process_redirects(t_token **start, t_exec_node *cmd,
		t_shell *shell)
{
	t_token	*curr;

	curr = *start;
	while (curr && curr->next)
	{
		if (curr->type == TOKEN_PIPE)
			break ;
		if (process_single_redirect(&curr, cmd, shell) < 0)
			return (-1);
		curr = curr->next;
	}
	return (0);
}

t_exec_node	*wrap_with_redirects(t_token *start, t_token *end, t_shell *shell)
{
	t_exec_node	*cmd;

	cmd = create_command_node(start, end);
	if (!cmd)
		return (NULL);
	if (process_redirects(&start, cmd, shell) < 0)
		return (free_execution_tree(cmd, 1), NULL);
	return (cmd);
}
