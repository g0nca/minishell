/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:06:08 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/04 14:23:18 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		if (str1 != str2 && str1[i] < str2[i])
			return (-1);
		if (str1 != str2 && str1[i] > str2[i])
			return (1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
    char data1[] = "12345678934534";
    char data2[] = "1234567";
    printf("Valor:%i\n", ft_memcmp(data1, data2, 20));
    return(0);
}
*/
