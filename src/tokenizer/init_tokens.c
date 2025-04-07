/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:32:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/07 11:34:54 by ggomes-v         ###   ########.fr       */
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