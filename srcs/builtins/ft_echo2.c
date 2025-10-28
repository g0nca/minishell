/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:09:36 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/28 09:11:44 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_redir_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HERE_DOC);
}

static void	print_tilde_expanded(t_token *token, t_shell *shell)
{
	char	*home;
	char	*expanded;

	home = cd_getenv(shell, "HOME");
	if (!home)
		home = getenv("HOME");
	if (home)
	{
		expanded = ft_strjoin(home, token->value + 1);
		if (expanded)
		{
			ft_printf_fd(1, "%s", expanded);
			free(expanded);
		}
	}
	else
		ft_printf_fd(1, "%s", token->value);
}

static void	print_token_value(t_token *token, t_shell *shell)
{
	if (token->value[0] == '~'
		&& (token->value[1] == '\0' || token->value[1] == '/'))
		print_tilde_expanded(token, shell);
	else
		ft_printf_fd(1, "%s", token->value);
}

void	ft_print_tokens(t_token *current, t_shell *shell)
{
	while (current)
	{
		if (is_redir_token(current))
		{
			current = current->next;
			if (current)
				current = current->next;
			continue ;
		}
		print_token_value(current, shell);
		current = current->next;
		if (current && !is_redir_token(current))
			ft_printf_fd(1, " ");
	}
}
