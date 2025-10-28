/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/28 12:29:33 by ggomes-v         ###   ########.fr       */
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
	if (check_unclosed_quotes(line, shell))
		return (1);
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
	if (simple_quote || double_quote)
		return (shell_error(shell, (char *)line, 7, EXIT_SUCCESS), 1);
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
