/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:06:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/06 12:43:45 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		while (big[i + j] == little[j] && big[i + j] && i + j < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
/*
int main(void)
{
    printf("%s\n", ft_strnstr("abcdefgh", "abc", 2));
    printf("%s\n", ft_strnstr("abcdefgh", "abc", 3));
    printf("%s\n", ft_strnstr("abcdefgh", "abc", 4));
    printf("%s\n", ft_strnstr("abcdefgh", "abc", 5));
    printf("%s\n", ft_strnstr("aaxx", "xx", 3));
    printf("%s\n", ft_strnstr("aaxx", "xx", 4));
    printf("%s\n", ft_strnstr("aaxx", "xx", 5));
    printf("%s\n", ft_strnstr("aaxx", "xx", 6));
    printf("%s\n", ft_strnstr("see FF your FF return FF now FF", "FF", 32));
    return(0);
}
*/
