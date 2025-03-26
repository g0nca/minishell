/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:05:45 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/06 12:54:04 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;
	size_t	j;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	if (size == 0 || lendst >= size)
		return (size + lensrc);
	i = lendst;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && i < size -1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (lendst + lensrc);
}
/*
#include <stdio.h>
int main(void)
{
    printf("%ld\n", ft_strlcat("pqrstuvwxyz", "abcd", 0));
    printf("%ld\n", ft_strlcat("pqrstuvwxyz", "abcd", 1));
    printf("%ld\n", ft_strlcat("pqrstuvwxyz", "abcd", 2));
    printf("%ld\n", ft_strlcat("pqrstuvwxyz", "abcd", 3));
    printf("%ld\n", ft_strlcat("pqrstuvwxyz", "abcd", 4));
    printf("%ld\n", ft_strlcat("pqrstuvwxyz", "abcd", 5));


    return(0);
}
*/
