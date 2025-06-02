/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:41:11 by andrade           #+#    #+#             */
/*   Updated: 2025/06/02 13:11:37 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
int	is_space(char c)
{
	return (c == ' ');
}
int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	skip_spaces(const char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	return (*i);
}
int skip_quotes(const char *str, int i)
{
	char quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}
