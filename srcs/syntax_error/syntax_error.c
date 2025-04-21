/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/21 15:13:35 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_quote(char c)
{
    return (c == '\'' || c == '\"');
}

int skip_quote(const char *str, int *i)
{
    char quote;
    quote = str[(*i)++];
    while (str[*i] && str[*i] != quote)
        (*i)++;
    if (str[*i] == quote)
        return (*i);
    return (-1); // erro: aspas não fechadas
}

int skip_spaces(const char *str, int *i)
{
    while (str[*i] && ft_isspace(str[*i]))
        (*i)++;
    return (*i);
}

/* int check_unclosed_quotes(const char *str, t_shell *shell, int *i)
{
    int closed;
    while (str[*i])
    {
        if (is_quote(str[*i]))
        {
            closed = skip_quote(str, i);
            if (closed == -1)
            {
                shell_error(shell, "minishell: unclosed quote", 12, EXIT_SUCCESS);
                return (1);
            }
            *i = closed;
        }
        (*i)++;
    }
    return (0);
} */
int	check_pipe(const char *str, t_shell *shell, int *i)
{
	(*i)++;
	*i = skip_spaces(str, i);
	if (!str[(*i)])
		return (shell_error(shell, "Syntax Error", 12, EXIT_SUCCESS), 1);
	return (0);
}
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
	int in_single = 0;
	int in_double;
	
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
int check_syntax_errors_main(const char *str, t_shell *shell)
{
    int i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
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
		i++;
	}
    return (0);
}

/* int check_syntax_errors_auxiliar(const char *str, t_shell *shell, int *i)
{
    while (str[*i])
    {
        if (is_quote(str[*i]))
            *i = skip_quote(str, i);
        else if (str[*i] == '|')
        {
            if (check_pipes(str, shell, i) == 1)
                return (1);
        }
        else if (str[*i] == '>' || str[*i] == '<')
        {
            if (check_redir(str, shell, i) == 1)
                return (1);
        }
        (*i)++;
    }
    return (0);
}

int check_redir(const char *str, t_shell *shell, int *i)
{
    char redir;
    redir = str[*i];
    (*i)++;
    if (str[*i] == redir) // >> ou <<
        (*i)++;
    *i = skip_spaces(str, i);
    if (str[*i] == '\0' || str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
    {
        shell_error(shell, "syntax error near unexpected token\n", 12, EXIT_SUCCESS);
        return (1);
    }
    return (0);
}

int check_pipes(const char *str, t_shell *shell, int *i)
{
    (*i)++;
    *i = skip_spaces(str, i);
    if (str[*i] == '|' || str[*i] == '\0')
    {
        shell_error(shell, "syntax error near unexpected token `|`\n", 12, EXIT_SUCCESS);
        return (1);
    }
    return (0);
} */
