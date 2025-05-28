/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:41:11 by andrade           #+#    #+#             */
/*   Updated: 2025/05/28 10:42:23 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	skip_quote(const char *str, int *i)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		return (*i);
	return (-1);
}

int	skip_spaces(const char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	return (*i);
}

int	check_pipe(const char *str, t_shell *shell, int *i)
{
	(*i)++;
	*i = skip_spaces(str, i);
	if (!str[(*i)])
		return (shell_error(shell, "Syntax Error", 12, EXIT_SUCCESS), 1);
	return (0);
}
