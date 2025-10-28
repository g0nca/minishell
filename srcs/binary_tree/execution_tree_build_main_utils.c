/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/09/24 10:21:53 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/27 13:25:12 by ggomes-v         ###   ########.fr       */
=======
/*   Created: 2025/09/24 09:44:39 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/24 10:11:14 by ggomes-v         ###   ########.fr       */
>>>>>>> Redirects_22_09
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

<<<<<<< HEAD
static int	handle_output_redirect_with_advance(t_token **curr_ptr,
			t_exec_node *cmd, t_shell *shell)
{
	t_token	*curr;

	curr = *curr_ptr;
	if (handle_output_redirect(curr, cmd, shell) < 0)
		return (-1);
	if (curr->next && curr->next->type == TOKEN_WORD)
		*curr_ptr = curr->next;
	return (0);
}

static int	handle_append_redirect_with_advance(t_token **curr_ptr,
			t_exec_node *cmd, t_shell *shell)
{
	t_token	*curr;

	curr = *curr_ptr;
	if (handle_append_redirect(curr, cmd, shell) < 0)
		return (-1);
	if (curr->next && curr->next->type == TOKEN_WORD)
		*curr_ptr = curr->next;
	return (0);
}

int	process_single_redirect(t_token **curr_ptr, t_exec_node *cmd,
			t_shell *shell)
{
	t_token	*curr;

	curr = *curr_ptr;
	if (curr->type == TOKEN_HERE_DOC)
		return (handle_heredoc_tree(curr, shell, cmd));
	else if (curr->type == TOKEN_REDIR_IN)
	{
		if (handle_input_redirect(curr, cmd, shell) < 0)
			return (-1);
		if (curr->next && curr->next->type == TOKEN_WORD)
			*curr_ptr = curr->next;
	}
	else if (curr->type == TOKEN_REDIR_OUT)
		return (handle_output_redirect_with_advance(curr_ptr, cmd,
				shell));
	else if (curr->type == TOKEN_APPEND)
		return (handle_append_redirect_with_advance(curr_ptr, cmd,
				shell));
	return (0);
}
=======
static int handle_output_redirect_with_advance(t_token **curr_ptr, 
                                             t_exec_node *cmd, 
                                             t_shell *shell, 
                                             t_redirs *redirs)
{
    t_token *curr = *curr_ptr;
    
    if (handle_output_redirect(curr, cmd, shell, redirs) < 0)
        return (-1);
    if (curr->next && curr->next->type == TOKEN_WORD)
        *curr_ptr = curr->next;
    return (0);
}

static int handle_append_redirect_with_advance(t_token **curr_ptr, 
                                             t_exec_node *cmd, 
                                             t_shell *shell, 
                                             t_redirs *redirs)
{
    t_token *curr = *curr_ptr;
    
    if (handle_append_redirect(curr, cmd, shell, redirs) < 0)
        return (-1);
    if (curr->next && curr->next->type == TOKEN_WORD)
        *curr_ptr = curr->next;
    return (0);
}

int process_single_redirect(t_token **curr_ptr, t_exec_node *cmd, 
                                  t_shell *shell, t_redirs *redirs)
{
    t_token *curr = *curr_ptr;
    
    if (curr->type == TOKEN_HERE_DOC)
        return (handle_heredoc_tree(curr, shell, redirs));
    else if (curr->type == TOKEN_REDIR_IN)
    {
        if (handle_input_redirect(curr, cmd, shell, redirs) < 0)
            return (-1);
        if (curr->next && curr->next->type == TOKEN_WORD)
            *curr_ptr = curr->next;
    }
    else if (curr->type == TOKEN_REDIR_OUT)
        return (handle_output_redirect_with_advance(curr_ptr, cmd, shell, redirs));
    else if (curr->type == TOKEN_APPEND)
        return (handle_append_redirect_with_advance(curr_ptr, cmd, shell, redirs));
    return (0);
}
>>>>>>> Redirects_22_09
