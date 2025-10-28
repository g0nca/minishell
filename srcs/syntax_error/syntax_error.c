/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/28 12:29:33 by ggomes-v         ###   ########.fr       */
=======
/*   Updated: 2025/05/29 14:01:03 by ggomes-v         ###   ########.fr       */
>>>>>>> PIPES
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_syntax_errors_main(const char *line, t_shell *shell)
{
<<<<<<< HEAD
	if (!line || !*line)
		return (0);
	if (check_starting_pipe(line, shell))
		return (1);
	if (check_double_pipes(line, shell))
		return (1);
	if (check_redirects(line, shell))
		return (1);
	if (check_heredoc_and_redirect_conflict(line, shell))
		return (1);
	if (check_unclosed_quotes(line, shell))
		return (1);
=======
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
int	check_pipe(const char *str, t_shell *shell, int *i)
{
	(*i)++;
	if (str[(*i)] == '|')
		return (shell_error(shell, "Syntax Error", 12, EXIT_SUCCESS), 1);
	*i = skip_spaces(str, i);
>>>>>>> PIPES
	return (0);
}

int	check_unclosed_quotes(const char *line, t_shell *shell)
{
	int	i;
	int	simple_quote;
	int	double_quote;

	simple_quote = 0;
	double_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_quote)
			simple_quote = !simple_quote;
		else if (line[i] == '\"' && !simple_quote)
			double_quote = !double_quote;
		i++;
	}
<<<<<<< HEAD
	if (simple_quote || double_quote)
		return (shell_error(shell, (char *)line, 7, EXIT_SUCCESS), 1);
=======
	if (!str[(*i)])
		return (shell_error(shell, "Syntax Error: redirect", 12, EXIT_SUCCESS), 1);
>>>>>>> PIPES
	return (0);
}

int	check_starting_pipe(const char *line, t_shell *shell)
{
<<<<<<< HEAD
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '|')
	{
		shell_error(shell, "`|'", 7, EXIT_SUCCESS);
=======
	int in_single;
	int in_double;
	
	in_single = 0;
	in_double = 0;
	while (str[(*i)])
	{
		if (str[(*i)] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[(*i)] == '\"' && !in_single)
			in_double = !in_double;
		(*i)++;
	}
	if (in_single == 1 || in_double == 1)
	{
		shell_error(shell, "Syntax Error: unclosed quote", 12, EXIT_SUCCESS);
>>>>>>> PIPES
		return (1);
	}
	return (0);
}

int	check_heredoc_and_redirect_conflict(const char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
			i = skip_quotes(line, i);
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] && is_space(line[i]))
				i++;
			if (is_redirect(line[i]))
				return (shell_error(shell, "", 4, EXIT_SUCCESS), 1);
		}
<<<<<<< HEAD
		else
=======
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
		else if (str[i])
>>>>>>> PIPES
			i++;
	}
	return (0);
}
