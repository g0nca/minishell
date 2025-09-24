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
	cmd->fd_in = open(filename, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		shell_error(shell, filename, 15, EXIT_SUCCESS);
		return (-1);
	}
	return (0);
}

int  open_output_file(t_exec_node *cmd, char *filename,
        int append, t_shell *shell)
{
	int	fd_out;

	if (append == 1)
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
}

t_exec_node	*wrap_with_redirects(t_token *start, t_token *end, t_shell *shell)
{
	t_exec_node	*cmd;
	t_redirs	redirs;

	ft_bzero(&redirs, sizeof(redirs));
	cmd = create_command_node(start, end);
	if (!cmd)
		return (NULL);
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
	return (cmd);
}