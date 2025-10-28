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

<<<<<<< HEAD
int	open_input_file(t_exec_node *cmd, char *filename, t_shell *shell)
{
	(void)cmd;
	if (access(filename, F_OK | R_OK) == -1)
	{
		shell_error(shell, filename, 15, EXIT_SUCCESS);
=======
static int	open_input_file(t_exec_node *cmd, char *filename, t_shell *shell)
{
	cmd->fd_in = open(filename, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		shell_error(shell, filename, 2, EXIT_SUCCESS);
>>>>>>> fix_errors
		return (-1);
	}
	return (0);
}

<<<<<<< HEAD
<<<<<<< HEAD
int	open_output_file(t_exec_node *cmd, char *filename,
		int append, t_shell *shell)
=======
int  open_output_file(t_exec_node *cmd, char *filename,
        int append, t_shell *shell)
>>>>>>> Redirects_22_09
{
	(void)shell;
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	if (append == 1)
<<<<<<< HEAD
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
=======
static int  open_output_file(t_exec_node *cmd, char *filename,
        int append, t_shell *shell)
{
    static int  error_reported;

	error_reported = 0;
	if (append != 1)
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
>>>>>>> fix_errors
		curr = curr->next;
	}
	return (0);
=======
        fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
		fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        shell_error(shell, filename, 3, EXIT_SUCCESS);
        return (-1);
    }
	else 
		cmd->fd_out = fd_out;
    return (0);
}

static int process_redirects(t_token **start, t_exec_node *cmd, 
                           t_shell *shell, t_redirs *redirs)
{
    t_token *curr;
    
    curr = *start;
    while (curr && curr->next)
    {
        if (curr->type == TOKEN_PIPE)
            break;
            
        if (process_single_redirect(&curr, cmd, shell, redirs) < 0)
            return (-1);
            
        curr = curr->next;
    }
    return (0);
>>>>>>> Redirects_22_09
}

t_exec_node	*wrap_with_redirects(t_token *start, t_token *end, t_shell *shell)
{
	t_exec_node	*cmd;

	cmd = create_command_node(start, end);
	if (!cmd)
		return (NULL);
<<<<<<< HEAD
<<<<<<< HEAD
	if (process_redirects(&start, cmd, shell) < 0)
		return (free_execution_tree(cmd, 1), NULL);
=======
	//ft_printf_fd(1, "TEST\n");
	if (process_redirects(&start, cmd, shell, &redirs) < 0)
	{
		//shell_error(shell, "", 15, EXIT_SUCCESS);
		return (free_execution_tree(cmd), NULL);
	}
	//print_exec_tree(cmd, 0);
	/*if (apply_redirects(cmd, &redirs) < 0)
	{
		shell->last_exit_status = 1;
		return (free_execution_tree(cmd), NULL);
	}*/
>>>>>>> Redirects_22_09
=======
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
>>>>>>> fix_errors
	return (cmd);
}
