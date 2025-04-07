/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:11:24 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/07 13:11:34 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    char *dup = malloc(n + 1);
    if (!dup)
        return NULL;

    for (size_t i = 0; i < n; i++)
        dup[i] = s[i];

    dup[n] = '\0';
    return dup;
}