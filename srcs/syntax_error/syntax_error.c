/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/28 10:42:17 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_redir(const char *str, t_shell *shell, int *i)
{
	(*i)++;
	if (str[(*i)] == '<' || str[(*i)] == '>')
		(*i)++;
	while (str[(*i)])
	{
		*i = skip_spaces(str, i);
		if (str[(*i)] != ' ' && str[(*i)] != '<' && str[(*i)] != '>')
			break ;
		if (str[(*i)] == '<' || str[(*i)] == '>')
			return (shell_error(shell, "Syntax Error", 12, EXIT_SUCCESS), 1);
	}
	if (!str[(*i)])
		return (shell_error(shell, "Syntax Error", 12, EXIT_SUCCESS), 1);
	return (0);
}

int	check_quote(const char *str, t_shell *shell, int *i)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (str[(*i)])
	{
		if (str[(*i)] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[(*i)] == '"' && !in_single)
			in_double = !in_double;
		(*i)++;
	}
	if (in_single || in_double)
	{
		shell_error(shell, "Syntax Error: unclosed quote", 12, EXIT_SUCCESS);
		return (1);
	}
	return (0);
}

int	check_syntax_errors_main(const char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (check_pipe(str, shell, &i))
				return (1);
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (check_redir(str, shell, &i))
				return (1);
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			if (check_quote(str, shell, &i))
				return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}
