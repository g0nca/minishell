/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:03:59 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/28 12:30:46 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_redirect_error(const char *line, int i, t_shell *shell)
{
	if (line[i] == '>' && line[i + 1] == '>')
		shell_error(shell, "`>>'", 7, EXIT_SUCCESS);
	else if (line[i] == '>')
		shell_error(shell, "`>'", 7, EXIT_SUCCESS);
	else if (line[i] == '<')
		shell_error(shell, "`<'", 7, EXIT_SUCCESS);
	return (1);
}

static int	validate_redirect_target(const char *line, int i, t_shell *shell)
{
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
	{
		shell_error(shell, "`newline'", 7, EXIT_SUCCESS);
		return (-1);
	}
	if (is_redirect(line[i]))
		return (-handle_redirect_error(line, i, shell));
	if (line[i] == '|')
	{
		shell_error(shell, "`|'", 7, EXIT_SUCCESS);
		return (-1);
	}
	return (i);
}

static int	process_redirect(const char *line, int i, t_shell *shell)
{
	char	c;

	c = line[i++];
	if (line[i] == c)
		i++;
	return (validate_redirect_target(line, i, shell));
}

int	check_redirects(const char *line, t_shell *shell)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
			i = skip_quotes(line, i);
		else if (is_redirect(line[i]))
		{
			i = process_redirect(line, i, shell);
			if (i < 0)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
