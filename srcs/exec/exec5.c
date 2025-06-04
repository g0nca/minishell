/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:11:32 by andrade           #+#    #+#             */
/*   Updated: 2025/06/04 11:04:47 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_args(t_token *token)
{
	int	count;
	t_token *current;

	count = 0;
	current = token;
	while (current)
	{
		if (current->type == TOKEN_CMD || current->type == TOKEN_WORD)
		{
			count++;
			current = current->next;
		}
		else if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_APPEND || current->type == TOKEN_HERE_DOC)
		{
			// Skip the redirection operator
			current = current->next;
			// Skip the filename if it exists
			if (current && current->type == TOKEN_WORD)
				current = current->next;
		}
		else if (current->type == TOKEN_PIPE)
		{
			// Stop at pipe - don't count arguments for next command
			break;
		}
		else
		{
			current = current->next;
		}
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
	int		i;
	t_token	*current;

	i = 0;
	current = token;
	while (current)
	{
		if (current->type == TOKEN_CMD || current->type == TOKEN_WORD)
		{
			args[i] = ft_strdup(current->value);
			if (!args[i])
			{
				// Clean up on malloc failure
				while (--i >= 0)
					free(args[i]);
				return;
			}
			i++;
			current = current->next;
		}
		else if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_APPEND || current->type == TOKEN_HERE_DOC)
		{
			// Skip the redirection operator
			current = current->next;
			// Skip the filename if it exists
			if (current && current->type == TOKEN_WORD)
				current = current->next;
		}
		else if (current->type == TOKEN_PIPE)
		{
			// Stop at pipe - don't process arguments for next command
			break;
		}
		else
		{
			current = current->next;
		}
	}
	args[i] = NULL;
}