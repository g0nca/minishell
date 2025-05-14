/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:18:33 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/14 10:32:37 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_echo(t_token *list, t_shell *shell)
{
    t_token *current;
    int n_flag;
    
    n_flag = 0;
    current = list->next;
    
    // Skip over redirection tokens and their arguments
    while (current && (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT || 
                       current->type == TOKEN_APPEND || current->type == TOKEN_HERE_DOC))
    {
        current = current->next; // Skip the redirection token
        if (current)
            current = current->next; // Skip the redirection target
    }
    
    // Check for -n flag
    while (current && ft_strncmp(current->value, "-n", 2) == 0)
    {
        // Make sure every character after "-n" is 'n'
        int valid_flag = 1;
        size_t i = 2;
        while (current->value[i])
        {
            if (current->value[i] != 'n')
            {
                valid_flag = 0;
                break;
            }
            i++;
        }
        
        if (!valid_flag)
            break;
            
        n_flag = 1;
        current = current->next;
        
        // Skip any redirections after the flag
        while (current && (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT || 
                         current->type == TOKEN_APPEND || current->type == TOKEN_HERE_DOC))
        {
            current = current->next; // Skip the redirection token
            if (current)
                current = current->next; // Skip the redirection target
        }
    }
    
    // Print the arguments
    while (current)
    {
        // Skip redirection tokens and their arguments
        if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT || 
            current->type == TOKEN_APPEND || current->type == TOKEN_HERE_DOC)
        {
            current = current->next; // Skip the redirection token
            if (current)
                current = current->next; // Skip the redirection target
            continue;
        }
        
        ft_printf_fd(STDOUT_FILENO, "%s", current->value);
        current = current->next;
        if (current && !(current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT || 
                        current->type == TOKEN_APPEND || current->type == TOKEN_HERE_DOC))
            ft_printf_fd(STDOUT_FILENO, " ");
    }
    
    if (!n_flag)
        ft_printf_fd(STDOUT_FILENO, "\n");
        
    shell->last_exit_status = EXIT_SUCCESS;
}