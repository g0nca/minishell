/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/25 16:08:07 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_pipe_error(const char *line, int *i, t_shell *shell)
{
	int	original_i;

	original_i = *i;
	(*i)++;
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	if (line[*i] == '|')
	{
		shell_error(shell, "`|'", 7, 2);
		return (1);
	}
	else if (line[*i] == '\0')
	{
		shell_error(shell, "`|'", 7, 2);
		return (1);
	}
	*i = original_i;
	return (0);
}

static int	check_pipe(const char *line, int *i,
		int *pipe_count, t_shell *shell)
{
	(*pipe_count)++;
	if (*pipe_count == 2)
	{
		shell_error(shell, "`||'", 7, 2);
		return (1);
	}
	if (handle_pipe_error(line, i, shell))
		return (1);
	return (0);
}

static int	process_pipe_char(const char *line, int *i, int *pipe_count,
		t_shell *shell)
{
	if (!*pipe_count)
		return (shell_error(shell, "`|'", 7, 2), 1);
	if (check_pipe(line, i, pipe_count, shell))
		return (1);
	(*i)++;
	return (0);
}

int	check_double_pipes(const char *line, t_shell *shell)
{
	int i;
	int pipe_count;
	int found_content;

	found_content = 0;
	i = 0;
	pipe_count = 0;
	while (line[i] && is_space(line[i]))
		i++;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			found_content = 1;
			i = skip_quotes(line, i);
		}
		else if (line[i] == '|')
		{
			if (!found_content && process_pipe_char(line, &i, &pipe_count, shell))
				return (1);
			else if (found_content && (check_pipe(line, &i, &pipe_count, shell) || ++i))
				return (1);
		}
		else if (!is_space(line[i]) && (found_content = 1) && (pipe_count = 0))
			i++;
		else
			i++;
	}
	return (0);
}
