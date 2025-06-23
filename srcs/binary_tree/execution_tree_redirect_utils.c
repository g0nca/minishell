/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_redirect_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:10:37 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:12:23 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT || type == TOKEN_APPEND);
}

t_exec_node	*create_redirect_node(t_token *start, t_token *curr, t_token *end)
{
    t_exec_node	*node;

    node = malloc(sizeof(t_exec_node));
    if (!node)
        return (NULL);
    node->type = get_redirect_node_type(curr->type);
    node->cmd = malloc(sizeof(char *) * 2);
    if (!node->cmd)
    {
        free(node);
        return (NULL);
    }
    node->cmd[0] = ft_strdup(curr->next->value);
    node->cmd[1] = NULL;
    node->fd_in = -1;
    node->fd_out = -1;

    // O comando deve ser criado com TODOS os argumentos, menos o operador e o ficheiro
    // Por isso, passa start e end para build_execution_tree, mas...
    // ...garante que a função que constrói o comando ignora o operador e o ficheiro!
    node->left = build_execution_tree_skip_redirect(start, curr, end);

    node->right = NULL;
    return (node);
}

t_exec_node *build_execution_tree_skip_redirect(t_token *start, t_token *redirect, t_token *end)
{
    t_token *current;
    t_exec_node *node;
    t_token *filtered_start;
    t_token *filtered_end;

    current = start;
    node = NULL;
    filtered_start = NULL;
    filtered_end = NULL;
    while (current && current != end)
    {
        if (current == redirect)
        {
            current = current->next;
            if (current && current != end)
                current = current->next;
            continue;
        }
        if (!filtered_start)
            filtered_start = current;
        current = current->next;
    }
    filtered_end = end;
    node = create_command_node(filtered_start, filtered_end);
    return (node);
}

t_exec_node	*find_and_create_redirect_node(t_token *start, t_token *end, t_shell *shell)
{
    t_token	*curr;
    t_token *last_redir = NULL;
    t_token *tmp;
    int     error_found = 0;

    // Find last input redirection
    curr = start;
    while (curr && curr != end && curr->next)
    {
        if (is_redirection(curr->type) && curr->next->type == TOKEN_WORD)
            last_redir = curr;
        curr = curr->next;
    }

    // Check all previous input redirections for file existence
    tmp = start;
    while (tmp && tmp != end && tmp->next)
    {
        if (is_redirection(tmp->type) && tmp->next->type == TOKEN_WORD)
        {
            if (access(tmp->next->value, F_OK) != 0)
            {
                if (!error_found)
                {
                    shell_error(shell, tmp->next->value, 2, false); // Report error
                }
                error_found = 1; // Mark that an error occurred
            }
        }
        tmp = tmp->next;
    }

    // Set exit code based on errors found
    if (error_found)
        shell->last_exit_status = 1; // Bash sets exit code to 1 for missing files
    else
        shell->last_exit_status = 0;

    if (last_redir)
        return (create_redirect_node(start, last_redir, end));
    return (NULL);
}

/* t_exec_node	*find_and_create_redirect_node(t_token *start, t_token *end)
{
    t_token	*curr;
    t_token *last_redir = NULL;
    t_token *tmp;

    // Find last input redirection
    curr = start;
    while (curr && curr != end && curr->next)
    {
        if (is_redirection(curr->type) && curr->next->type == TOKEN_WORD)
            last_redir = curr;
        curr = curr->next;
    }

    // Check all previous input redirections for file existence
    tmp = start;
    while (tmp && tmp != end && tmp->next)
    {
        if (is_redirection(tmp->type) && tmp->next->type == TOKEN_WORD && tmp != last_redir)
        {
            if (tmp->type == TOKEN_REDIR_IN)
            {
                if (access(tmp->next->value, F_OK) != 0)
                {
                    ft_error(2, tmp->next->value); // No such file or directory
                    g_exit_status = 1;
                    return (NULL);
                }
            }
        }
        tmp = tmp->next;
    }

    if (last_redir)
        return (create_redirect_node(start, last_redir, end));
    return (NULL);
}
 */
