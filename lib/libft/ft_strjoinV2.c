/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinV2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:15:21 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/03/19 13:05:45 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinv2(char const *s1, char const *s2)
{
	char	*str1;
	size_t	total_len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str1 = malloc((total_len + 2) * sizeof(char));
	if (!str1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str1[i] = s1[i];
		i++;
	}
	if (s1[i - 1] != '/')
		str1[i++] = '/';
	j = 0;
	while (s2[j])
		str1[i++] = s2[j++];
	str1[i] = '\0';
	return (str1);
}

/*
int	main(void)
{
	const char str1[] = "";
	const char str2[] = "";
	
	printf("%s\n", ft_strjoin(str1, str2));
	return(0);
}
*/
