/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/24 14:10:22 by joaomart         ###   ########.fr       */
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
		shell_error(shell, "`|'", 7, EXIT_SUCCESS);
		return (1);
	}
	else if (line[*i] == '\0')
	{
		shell_error(shell, "`|'", 7, EXIT_SUCCESS);
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
		shell_error(shell, "`||'", 7, EXIT_SUCCESS);
		return (1);
	}
	if (handle_pipe_error(line, i, shell))
		return (1);
	return (0);
}

static int	handle_pipe(const char *line, t_parser *p, t_shell *shell)
{
	if (!p->found_content && p->pipe_count == 0)
	{
		shell_error(shell, "`|'", 7, EXIT_SUCCESS);
		return (1);
	}
	if (check_pipe(line, &p->i, &p->pipe_count, shell))
		return (1);
	p->i++;
	return (0);
}

static void	handle_content(const char *line, t_parser *p)
{
	if (!is_space(line[p->i]))
	{
		p->found_content = 1;
		p->pipe_count = 0;
	}
	p->i++;
}

int	check_double_pipes(const char *line, t_shell *shell)
{
	t_parser	p;

	p.i = 0;
	p.pipe_count = 0;
	p.found_content = 0;
	while (line[p.i] && is_space(line[p.i]))
		p.i++;
	while (line[p.i])
	{
		if (is_quote(line[p.i]))
		{
			p.found_content = 1;
			p.i = skip_quotes(line, p.i);
		}
		else if (line[p.i] == '|')
		{
			if (handle_pipe(line, &p, shell))
				return (1);
		}
		else
			handle_content(line, &p);
	}
	return (0);
}
