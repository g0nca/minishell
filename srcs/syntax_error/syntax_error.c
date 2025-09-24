/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/24 10:11:44 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_syntax_errors_main(const char *line, t_shell *shell)
{
	if (!line || !*line)
		return (0);

	// Primeiro verificar se linha começa com pipe
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

// Nova função para verificar pipe no início
int	check_starting_pipe(const char *line, t_shell *shell)
{
	int i = 0;

	// Pular espaços no início
	while (line[i] && is_space(line[i]))
		i++;

	// Se encontrar pipe logo no início
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
			while (line[i] && is_space(line[i]))
				i++;

			// Verificar o que vem após o redirect
			if (!line[i])
			{
				// Fim da linha - token newline
				shell_error(shell, "`newline'", 7, EXIT_SUCCESS);
				return (1);
			}
			else if (is_redirect(line[i]))
			{
				// Outro redirect - mostrar o token específico
				if (line[i] == '>' && line[i + 1] == '>')
					shell_error(shell, "`>>'", 7, EXIT_SUCCESS);
				else if (line[i] == '>')
					shell_error(shell, "`>'", 7, EXIT_SUCCESS);
				else if (line[i] == '<')
					shell_error(shell, "`<'", 7, EXIT_SUCCESS);
				return (1);
			}
			else if (line[i] == '|')
			{
				shell_error(shell, "`|'", 7, EXIT_SUCCESS);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}
