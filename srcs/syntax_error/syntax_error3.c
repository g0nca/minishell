/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:03 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/24 10:12:03 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_pipe_error(const char *line, int *i, t_shell *shell)
{
	int original_i = *i;

	(*i)++;
	while (line[*i] && is_space(line[*i]))
		(*i)++;

	// Se encontrar outro pipe ou fim da linha
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

	// Reset do índice para continuar o processamento normal
	*i = original_i;
	return (0);
}

static int	check_pipe(const char *line, int *i,
		int *pipe_count, t_shell *shell)
{
	(*pipe_count)++;
	if (*pipe_count == 2)
	{
		shell_error(shell, "`||'", 7, 2);  // Correção aqui também
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
	int	found_content = 0;  // Flag para verificar se há conteúdo antes do pipe

	i = 0;
	pipe_count = 0;

	// Pular espaços iniciais
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
			// Se não há conteúdo antes do primeiro pipe
			if (!found_content && pipe_count == 0)
			{
				shell_error(shell, "`|'", 7, 2);
				return (1);
			}

			if (check_pipe(line, &i, &pipe_count, shell))
				return (1);
			i++;
		}
		else if (!is_space(line[i]))
		{
			found_content = 1;
			pipe_count = 0;
			i++;
		}
		else
			i++;
	}
	return (0);
}
