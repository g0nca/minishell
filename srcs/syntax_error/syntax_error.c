/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/15 14:03:54 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	skip_quote(const char *str, int i)
{
	char quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		return (i);
	return (-1); // erro: aspas não fechadas
}

int	skip_spaces(const char *str, int i)
{
	while (str[i] && isspace(str[i]))
		i++;
	return (i);
}

int	check_unclosed_quotes(const char *str, t_shell *shell)
{
	int i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			int closed = skip_quote(str, i);
			if (closed == -1)
			{
				shell_error(shell, "minishell: unclosed quote", 12, EXIT_SUCCESS);
				return (1);
			}
			i = closed;
		}
		i++;
	}
	return (0);
}

int	check_syntax_errors(const char *str, t_shell *shell)
{
	int i = 0;

	if (check_unclosed_quotes(str, shell))
		return (1);
	i = skip_spaces(str, i);
	if (str[i] == '|')
	{
		printf("syntax error near unexpected token `|`\n");
		return (1);
	}
	while (str[i])
	{
		if (is_quote(str[i]))
			i = skip_quote(str, i);
		else if (str[i] == '|')
		{
			i++;
			i = skip_spaces(str, i);
			if (str[i] == '|' || str[i] == '\0')
			{
				printf("syntax error near unexpected token `|`\n");
				return (1);
			}
		}
		else if (str[i] == '>' || str[i] == '<')
		{
			char redir = str[i];
			i++;
			if (str[i] == redir) // >> ou <<
				i++;
			i = skip_spaces(str, i);
			if (str[i] == '\0' || str[i] == '|' || str[i] == '>' || str[i] == '<')
			{
				printf("syntax error near unexpected token `%c`\n", str[i] ? str[i] : 'n');
				return (1);
			}
		}
		i++;
	}
	return (0);
}

/*
int	check_syntax_errors(char *line)
{
	int i;
	int quotes;

	quotes = 0;
	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if ()
		i++;
	}
	return (0);
} */
/* int		check_syntax_error_token(int token_type, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		
	}
}
 */