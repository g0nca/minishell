/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:31:29 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/04 14:49:58 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s1);
	str = 0;
	if (s1 != 0 && set != 0)
	{
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[i] && ft_strchr(set, s1[j - 1]))
			j--;
		str = (char *) malloc((j - i + 1) * sizeof(char));
		if (str)
		{
			ft_strlcpy(str, &s1[i], j - i + 1);
			return (str);
		}
	}
	return (NULL);
}
/*
int	main(void)
{
	const char str1[] = "aaababbbaaaMy name is Goncaloaaabbaba";
	const char str2[] = "ab";
	
	printf("trimstring: %s", ft_strtrim(str1, str2));
	return(0);
}
*/
