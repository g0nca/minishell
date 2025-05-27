/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:11:32 by andrade           #+#    #+#             */
/*   Updated: 2025/05/27 21:50:04 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == TOKEN_CMD || token->type == TOKEN_WORD
			|| token->type == TOKEN_DOUBLE_QUOTE
			|| token->type == TOKEN_SIMPLE_QUOTE)
			count++;
		else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HERE_DOC)
		{
			token = token->next;
			if (!token)
				break ;
			continue ;
		}
		token = token->next;
	}
	return (count);
}

char	**allocate_args(int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	return (args);
}

void	fill_args(t_token *token, char **args)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == TOKEN_CMD || token->type == TOKEN_WORD
			|| token->type == TOKEN_DOUBLE_QUOTE
			|| token->type == TOKEN_SIMPLE_QUOTE)
			args[i++] = ft_strdup(token->value);
		else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HERE_DOC)
		{
			token = token->next;
			if (!token)
				break ;
			continue ;
		}
		token = token->next;
	}
	args[i] = NULL;
}
