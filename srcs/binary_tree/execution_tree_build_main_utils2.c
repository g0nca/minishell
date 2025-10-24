/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main_utils2.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:23:10 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/24 16:08:11 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int handle_heredoc_tree(t_token *curr, t_shell *shell, t_exec_node *cmd)
{
    char **new_array;
    int count;
    int i;
    
    (void)shell;
    if (curr->next && curr->next->type == TOKEN_WORD)
    {
        count = 0;
        if (cmd->heredoc_delimiters)
        {
            while (cmd->heredoc_delimiters[count])
                count++;
        }
        new_array = malloc(sizeof(char *) * (count + 2));
        if (!new_array)
            return (-1);
        i = 0;
        while (i < count)
        {
            new_array[i] = cmd->heredoc_delimiters[i];
            i++;
        }
        new_array[count] = ft_strdup(curr->next->value);
        if (!new_array[count])
        {
            free(new_array);
            return (-1);
        }
        new_array[count + 1] = NULL;
        if (cmd->heredoc_delimiters)
            free(cmd->heredoc_delimiters);
        cmd->heredoc_delimiters = new_array;
        cmd->last_redir_in = curr->next->value;
        cmd->last_redir_in_type = 6;
    }
    return (0);
}

int	handle_input_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		if (open_input_file(cmd, curr->next->value, shell) < 0)
			return (-1);
		cmd->input_file = curr->next->value;
		if (!cmd->input_file)
			return (-1);
		if (cmd->last_redir_in != NULL && cmd->last_redir_in_type != 0)
		{
			cmd->last_redir_in = NULL;
			cmd->last_redir_in_type = 0;
		}
		cmd->last_redir_in = curr->next->value;
		cmd->last_redir_in_type = 3;
	}
	return (0);
}

int	handle_output_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		if (open_output_file(cmd, curr->next->value, false, shell) < 0)
			return (-1);
		cmd->output_file = curr->next->value;
		if (!cmd->output_file)
			return (-1);
		cmd->append_file = NULL;
	}
	return (0);
}

int	handle_append_redirect(t_token *curr, t_exec_node *cmd,
		t_shell *shell)
{
	if (curr->next && curr->next->type == TOKEN_WORD)
	{
		if (open_output_file(cmd, curr->next->value, true, shell) < 0)
			return (-1);
		cmd->append_file = curr->next->value;
		if (!cmd->append_file)
			return (-1);
		cmd->output_file = NULL;
	}
	return (0);
}
