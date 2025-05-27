/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:36:43 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/27 15:40:43 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*remove_all_quotes(char *value)
{
	char	*cleaned;
	int		i, j;

	if (!value)
		return (NULL);
	cleaned = malloc(ft_strlen(value) + 1);
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] != '"' && value[i] != '\'')
		{
			cleaned[j] = value[i];
			j++;
		}
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}


char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}
