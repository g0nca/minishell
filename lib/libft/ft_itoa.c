/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:05:00 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/06 16:24:39 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned int	count_numbers(int nbr)
{
	unsigned int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		count += 1;
	while (nbr != '\0')
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;
	unsigned int	nbr;

	len = count_numbers(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr == 0)
		str[0] = '0';
	str[len] = '\0';
	while (nbr != 0)
	{
		str[len - 1] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(1000034));
        printf("%s\n", ft_itoa(-10004));
        printf("%s\n", ft_itoa(2147483647));
        printf("%s\n", ft_itoa(-2147483647));
        printf("%s\n", ft_itoa(1000034));
        printf("%s\n", ft_itoa(0));

	return(0);
}*/
