/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:18 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/21 16:01:50 by ggomes-v         ###   ########.fr       */
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
    t_token *current;
    t_token *next;

    if (!list)
        return;
    current  = list;
    while (current)
    {
        next = current->next; // Save the next node before freeing
        if (current->value) // Free the token's value
            free(current->value);
        free(current); // Free the token itself
        current = next; // Move to the next token
    }
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
