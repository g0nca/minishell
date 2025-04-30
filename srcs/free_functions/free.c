/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:18 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/30 16:07:18 by joaomart         ###   ########.fr       */
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

void free_tokens(t_token **list)
{
    t_token *next;

    if (!*list)
        return;

    while (*list)
    {
        next = (*list)->next; // Save the next node before freeing

        // Close heredoc file descriptor if it's open
        if ((*list)->heredoc_fd != -1)
        {
            close((*list)->heredoc_fd);
            (*list)->heredoc_fd = -1;
        }

        if ((*list)->value) // Free the token's value
        {
            free((*list)->value);
            (*list)->value = NULL;
        }

        free((*list)); // Free the token itself
        (*list) = next; // Move to the next token
    }

    (*list) = NULL;
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
