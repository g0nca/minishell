/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_token_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:12:40 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/06/30 11:34:17 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_valid_tokens(t_token *start, t_token *end)
{
	int		count;
	t_token	*tmp;
	int		skip_next;

	tmp = start;
	count = 0;
	skip_next = 0;
	while (tmp && tmp != end)
	{
		if (skip_next)
		{
			skip_next = 0;
			tmp = tmp->next;
			continue ;
		}
		if (is_redirection(tmp->type))
			skip_next = 1;
		else if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
			count++;
		tmp = tmp->next;
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

int	add_token_to_argv(char **argv, int i, char *value)
{
	argv[i] = ft_strdup(value);
	if (!argv[i])
	{
		cleanup_argv_on_error(argv, i);
		return (0);
	}
	return (1);
}

void	fill_argv_array(t_token *start, t_token *end, char **argv, int *count)
{
	t_token	*tmp;
	int		i;
	int		skip_next;

	i = 0;
	tmp = start;
	skip_next = 0;
	while (tmp && tmp != end && i < *count)
	{
		if (skip_next)
		{
			skip_next = 0;
			tmp = tmp->next;
		}
		if (is_redirection(tmp->type))
			skip_next = 1;
		else if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
		{
			if (!add_token_to_argv(argv, i, tmp->value))
				return ;
			i++;
		}
		tmp = tmp->next;
	}
	argv[i] = NULL;
}
