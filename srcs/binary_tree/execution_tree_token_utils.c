/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_token_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:12:40 by ggomes-v          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/30 11:34:17 by ggomes-v         ###   ########.fr       */
=======
/*   Updated: 2025/05/29 11:16:33 by ggomes-v         ###   ########.fr       */
>>>>>>> PIPES
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

<<<<<<< HEAD
=======
static int	should_skip_redirection(t_token *tmp)
{
	if (tmp->next && is_redirection(tmp->next->type))
		return (1);
	return (0);
}

>>>>>>> PIPES
int	count_valid_tokens(t_token *start, t_token *end)
{
	int		count;
	t_token	*tmp;
<<<<<<< HEAD
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
=======

	tmp = start;
	count = 0;
	while (tmp && tmp != end)
	{
		if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
		{
			if (tmp->next && is_redirection(tmp->next->type))
			{
				tmp = tmp->next->next;
				continue ;
			}
			count++;
		}
>>>>>>> PIPES
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

<<<<<<< HEAD
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
=======
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
			if (should_skip_redirection(tmp))
			{
				tmp = tmp->next->next;
				continue ;
			}
			argv[i] = strdup(tmp->value);
			if (!argv[i])
			{
				cleanup_argv_on_error(argv, i);
				return ;
			}
>>>>>>> PIPES
			i++;
		}
		tmp = tmp->next;
	}
	argv[i] = NULL;
}
