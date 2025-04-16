/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:06:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/16 10:53:08 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ternary_operator(t_token *list, char quote)
{
	if (quote == '\"')
	{
		list->type_quotes = 2;
		return (2);
	}
	else if (quote == '\'')
	{
		list->type_quotes = 1;	
		return (1);
	}
	else
	{
		list->type_quotes = 0;
		return (0);
	}
		
}