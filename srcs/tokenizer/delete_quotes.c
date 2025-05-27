/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:25:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/27 12:47:45 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t  size_counter_without_quotes(t_token *current)
{
    int     i;
    size_t  n_bytes;

    i = 0;
    n_bytes = 0;
    while (current->value[i])
    {
        if (current->value[i] == '\"') 
            current->in_double_quotes = !current->in_double_quotes;
        else if (current->value[i] == '\'' && current->in_double_quotes == 0)
            current->in_single_quotes = !current->in_single_quotes;
        else if (current->in_double_quotes == 1)
            n_bytes++;
        else if (current->in_single_quotes == 1)
            n_bytes++;
        i++;
    }
    return (n_bytes);
}
int     delete_quotes(t_token **list, t_shell *shell)
{
    t_token     *current;
    t_token     *next;
    size_t      n_bytes;
    (void)shell;
    
    if (!list || !*list)
        return (-1);
    current = *list;
    while (current)
    {
        next = current->next;
        n_bytes = size_counter_without_quotes(current);
        current = next;
    }
    return (0);
}

