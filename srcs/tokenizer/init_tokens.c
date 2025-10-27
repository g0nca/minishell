/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:32:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/27 13:32:29 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*init_token_struct_new_node(t_token *list, t_token_type type)
{
	list->next = NULL;
	list->prev = NULL;
	list->type = type;
	list->size = 0;
	list->expansion = 0;
	list->type_quotes = 0;
	list->dollar_sign = 0;
	list->in_double_quotes = 0;
	list->in_single_quotes = 0;
	return (list);
}

t_token	*init_token_struct_inicial(t_token *list)
{
	list->next = NULL;
	list->prev = NULL;
	list->value = NULL;
	list->type = -1;
	list->size = 0;
	list->expansion = 0;
	list->type_quotes = 0;
	list->dollar_sign = 0;
	list->in_double_quotes = 0;
	list->in_single_quotes = 0;
	return (list);
}
