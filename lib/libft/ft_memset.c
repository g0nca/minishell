/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:04:07 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/04 14:46:10 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(*(unsigned char *)(s + i)) = (unsigned char)(c);
		i++;
	}
	return ((void *)s);
}
/*
#include <stdio.h>
int main(void)
{
    char str[10];
    const char ch = '0';
    printf("Charater Found: %s\n", (char *)ft_memset(str, ch, sizeof(str)));
    return(0);
}
*/
