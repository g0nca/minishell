/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/06/30 11:22:29 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_pipe_error(const char *line, int *i, t_shell *shell)
{
	(*i)++;
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	if (line[*i] == '|' || line[*i] == '\0')
	{
		shell_error(shell, "", 7, EXIT_SUCCESS);
		return (1);
	}
	return (0);
}

static int	check_pipe(const char *line, int *i,
		int *pipe_count, t_shell *shell)
{
	(*pipe_count)++;
	if (*pipe_count == 2)
	{
		shell_error(shell, "`||`\n", 7, EXIT_SUCCESS);
		return (1);
	}
	if (handle_pipe_error(line, i, shell))
		return (1);
	return (0);
}

int	check_double_pipes(const char *line, t_shell *shell)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
			i = skip_quotes(line, i);
		else if (line[i] == '|')
		{
			if (check_pipe(line, &i, &pipe_count, shell))
				return (1);
		}
		else if (!is_space(line[i]))
		{
			pipe_count = 0;
			i++;
		}
		else
			i++;
	}
	return (0);
}
