/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:29:13 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/03 16:07:08 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int     parse_line(char *line)
{
    int i;
    int d_quotes;

    d_quotes = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == 34)
            d_quotes += 1;
        i++;
    }
    return (d_quotes);
}