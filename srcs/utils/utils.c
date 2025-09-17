/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:06:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/17 10:19:43 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ternary_operator(t_token *list, char quote)
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

int	my_wifexited(int status)
{
	return (my_wtermsig(status) == 0);
}

int	my_wifsignaled(int status)
{
	int	ts;

	ts = my_wtermsig(status);
	return (ts != 0 && ts != 0x7f);
}

int	my_wtermsig(int status)
{
	return (status & 0x7f);
}

int	manual_wexitstatus(int status)
{
	return ((status & 0xff00) >> 8);
}
