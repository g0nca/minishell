/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_token_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:12:40 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:16:33 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_valid_tokens(t_token *start, t_token *end)
{
	int		count;
	t_token	*tmp;

	tmp = start;
	count = 0;
	while (tmp && tmp != end)
	{
		if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
		{
			count++;
			tmp = tmp->next;
		}
		else if (is_redirection(tmp->type))
		{
			// Skip redirection operator
			tmp = tmp->next;
			// Skip filename - but CONTINUE processing after redirection
			if (tmp && tmp != end && tmp->type == TOKEN_WORD)
				tmp = tmp->next;
		}
		else if (tmp->type == TOKEN_PIPE)
		{
			break;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	return (count);
}

void	cleanup_argv_on_error(char **argv, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		free(argv[j]);
		j++;
	}
	free(argv);
}

void	fill_argv_array(t_token *start, t_token *end, char **argv, int count)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = start;
	while (tmp && tmp != end && i < count)
	{
		if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
		{
			argv[i] = ft_strdup(tmp->value);
			if (!argv[i])
			{
				cleanup_argv_on_error(argv, i);
				return ;
			}
			i++;
			tmp = tmp->next;
		}
		else if (is_redirection(tmp->type))
		{
			// Skip redirection operator
			tmp = tmp->next;
			// Skip filename - but CONTINUE processing after redirection
			if (tmp && tmp != end && tmp->type == TOKEN_WORD)
				tmp = tmp->next;
		}
		else if (tmp->type == TOKEN_PIPE)
		{
			break;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	argv[i] = NULL;
}
