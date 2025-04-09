/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:18:33 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/09 14:50:52 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

void	ft_echo(t_token_list *list, t_shell *shell)
{
	t_token *current;
	int no_newline;

	no_newline = 0;
	current = list->tokens->next;
	while (current && is_n_flag(current->value))
	{
		no_newline = 1;
		current = current->next;
	}
	while (current)
	{
		ft_printf_fd(STDOUT_FILENO, "%s", current->value);
		if (current->next)
			ft_printf_fd(STDOUT_FILENO, " ");
		current = current->next;
	}
	if (!no_newline)
		ft_printf_fd(STDOUT_FILENO, "\n");
	shell->last_exit_status = EXIT_SUCCESS;
}
