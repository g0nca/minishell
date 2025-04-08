/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:32:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/08 15:12:27 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_list    init_token_struct(t_token_list *list)
{
    list->tokens = NULL;
    list->size = 0;
    list->capacity = 0;
    return (*list);
}

t_token_list *init_token_list(void)
{
    t_token_list *list = malloc(sizeof(t_token_list));
    if (!list)
        return NULL;
    list->tokens = NULL;
    list->size = 0;
    list->capacity = 0; // não é necessário com lista encadeada, mas deixamos para compatibilidade
    return list;
}
