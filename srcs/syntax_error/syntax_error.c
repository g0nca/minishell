/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/06/02 13:18:42 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* int	check_redir(const char *str, t_shell *shell, int *i)
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

int	check_quote(const char *str, t_shell *shell)
{
	int	in_single;
	int	in_double;
	int i;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
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
			if (check_quote(str, shell))
				return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
} */

int	check_syntax_errors_main(const char *line, t_shell *shell)
{
	if (!line || !*line)
		return (0);
	if (check_double_pipes(line, shell))
		return (1);
	if (check_redirects(line, shell))
		return (1);
	if (check_heredoc_and_redirect_conflict(line, shell))
		return (1);
	return (0);
}
int	check_heredoc_and_redirect_conflict(const char *line, t_shell *shell)
{
	int i = 0;

	while (line[i])
	{
		if (is_quote(line[i]))
			i = skip_quotes(line, i);
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] && is_space(line[i])) i++;
			if (is_redirect(line[i]))
				return (shell_error(shell, "", 4, EXIT_SUCCESS), 1);
		}
		else
			i++;
	}
	return (0);
}
int	check_redirects(const char *line, t_shell *shell)
{
	int i = 0;

	while (line[i])
	{
		if (is_quote(line[i]))
			i = skip_quotes(line, i);
		else if (is_redirect(line[i]))
		{
			char c = line[i++];
			if (line[i] == c) i++; // skip >> or <<
			while (line[i] && is_space(line[i]))
				i++;
			if (!line[i] || is_redirect(line[i]) || line[i] == '|')
				return (shell_error(shell, "", 4, EXIT_SUCCESS), 1);
		}
		else
			i++;
	}
	return (0);
}
int	check_double_pipes(const char *line, t_shell *shell)
{
	int i;
	int pipe_count;

	i = 0;
	pipe_count = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
			i = skip_quotes(line, i);
		else if (line[i] == '|')
		{
			pipe_count++;
			if (pipe_count == 2)
				return (shell_error(shell,"`||`\n", 7, EXIT_SUCCESS), 1);
			i++;
			while (line[i] && is_space(line[i]))
				i++;
			if (line[i] == '|' || line[i] == '\0')
				return (shell_error(shell,"", 7, EXIT_SUCCESS), 1);
		}
		else if (!is_space(line[i]))
			pipe_count = 0, i++;
		else
			i++;
	}
	return (0);
}
