/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:18 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/10 11:17:32 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
void free_env(char **env)
{
    int i;

    i = 0;
    if (!env)
        return ;
    while (env[i])
        free(env[i++]);
    free(env);
}
// free the struct of t_shell
void    free_struct(t_shell *shell)
{
    free_env(shell->env);
    free(shell);
}
void free_tokens(t_token *list)
{
    if (!list)
        return;
        
    t_token *current = list;
    t_token *next;
    
    while (current)
    {
        next = current->next; // Save the next node before freeing
        
        // Free the token's value
        if (current->value)
            free(current->value);
            
        // Free the token itself
        free(current);
        
        current = next; // Move to the next token
    }
    
    // Don't free 'list' again - it was freed in the loop!
}
/* void free_tokens(t_token *list)
{
    t_token *current;
    t_token *next;

    current = list;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(list);
} */
