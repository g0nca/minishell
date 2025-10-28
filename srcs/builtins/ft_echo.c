/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:37:53 by andrade           #+#    #+#             */
/*   Updated: 2025/10/28 09:09:25 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_skip_redirections(t_token **current)
{
	while (*current && ((*current)->type == TOKEN_REDIR_IN
			|| (*current)->type == TOKEN_REDIR_OUT
			|| (*current)->type == TOKEN_APPEND
			|| (*current)->type == TOKEN_HERE_DOC))
	{
		*current = (*current)->next;
		if (*current)
			*current = (*current)->next;
	}
}

int	ft_check_n_flag(t_token **current)
{
	int		n_flag;
	int		valid_flag;
	size_t	i;

	n_flag = 0;
	while (*current && ft_strncmp((*current)->value, "-n", 2) == 0)
	{
		valid_flag = 1;
		i = 2;
		while ((*current)->value[i])
		{
			if ((*current)->value[i] != 'n')
			{
				valid_flag = 0;
				break ;
			}
			i++;
		}
		if (!valid_flag)
			break ;
		n_flag = 1;
		*current = (*current)->next;
		ft_skip_redirections(current);
	}
	return (n_flag);
}

void	ft_echo(t_token *list, t_shell *shell)
{
	t_token	*current;
	int		n_flag;

	current = list->next;
	ft_skip_redirections(&current);
	n_flag = ft_check_n_flag(&current);
	ft_print_tokens(current, shell);
	if (!n_flag)
		ft_printf_fd(1, "\n");
	shell->last_exit_status = EXIT_SUCCESS;
}
