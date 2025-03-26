/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:28:36 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/06 16:24:54 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signal;
	int	res;

	res = 0;
	signal = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		{
			signal = -signal;
		}
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += nptr[i] - 48;
		i++;
	}
	return (res * signal);
}
/*
#include <stdio.h>
int main(void)
{
    printf("%d\n", ft_atoi("--123"));
    printf("%d\n", ft_atoi("-+123"));
    printf("%d\n", ft_atoi("+-123"));
    printf("%d\n", ft_atoi("++123"));
    printf("%d\n", ft_atoi(""));
    printf("%d\n", ft_atoi("--+-+-997rer6786"));
    
    return(0);
}
*/
