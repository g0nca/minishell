/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:13:02 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/22 20:33:21 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_delimiters(char *str, const char *delimiters)
{
	const char	*delim;
	bool		is_delimiter;

	while (*str != '\0')
	{
		delim = delimiters;
		is_delimiter = false;
		while (*delim != '\0')
		{
			if (*str == *delim)
			{
				is_delimiter = true;
				break ;
			}
			delim++;
		}
		if (!is_delimiter)
			break ;
		str++;
	}
	return (str);
}

static char	*find_token_end(char *str, const char *delimiters)
{
	const char	*delim;

	while (*str != '\0')
	{
		delim = delimiters;
		while (*delim != '\0')
		{
			if (*str == *delim)
				return (str);
			delim++;
		}
		str++;
	}
	return (str);
}

static char	*get_cur_token(char *str, char *next_token, const char *delimiters)
{
	char	*current_token;

	if (str != NULL)
		current_token = str;
	else
		current_token = next_token;
	if (current_token == NULL)
		return (NULL);
	current_token = skip_delimiters(current_token, delimiters);
	if (*current_token == '\0')
		return (NULL);
	return (current_token);
}

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*next_token = NULL;
	char		*current_token;
	char		*token_start;

	current_token = get_cur_token(str, next_token, delimiters);
	if (current_token == NULL || *current_token == '\0')
	{
		next_token = NULL;
		return (NULL);
	}
	if (current_token == NULL)
		return (NULL);
	token_start = current_token;
	current_token = find_token_end(current_token, delimiters);
	if (*current_token != '\0')
	{
		*current_token = '\0';
		next_token = current_token + 1;
	}
	else
	{
		next_token = NULL;
	}
	return (token_start);
}
