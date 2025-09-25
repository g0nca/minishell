/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/25 15:57:32 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_syntax_errors_main(const char *line, t_shell *shell)
{
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
	return (0);
}

int	check_starting_pipe(const char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '|')
	{
		shell_error(shell, "`|'", 7, EXIT_SUCCESS);
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
		else
			i++;
	}
	return (0);
}

static int	validate_redirect_target(const char *line, int *i, t_shell *shell)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	if (!line[*i])
		return (shell_error(shell, "`newline'", 7, EXIT_SUCCESS), 1);
	if (is_redirect(line[*i]))
	{
		if (line[*i] == '>' && line[*i + 1] == '>')
			shell_error(shell, "`>>'", 7, EXIT_SUCCESS);
		else if (line[*i] == '>')
			shell_error(shell, "`>'", 7, EXIT_SUCCESS);
		else if (line[*i] == '<')
			shell_error(shell, "`<'", 7, EXIT_SUCCESS);
		return (1);
	}
	if (line[*i] == '|')
		return (shell_error(shell, "`|'", 7, EXIT_SUCCESS), 1);
	return (0);
}

int	check_redirects(const char *line, t_shell *shell)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
			i = skip_quotes(line, i);
		else if (is_redirect(line[i]))
		{
			c = line[i++];
			if (line[i] == c)
				i++;
			if (validate_redirect_target(line, &i, shell))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
