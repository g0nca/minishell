/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:25:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/22 11:00:24 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	size_counter_without_quotes(t_token *current)
{
	int		i;
	size_t	n_bytes;

	i = 0;
	n_bytes = 0;
	while (current->value[i])
	{
		if (current->value[i] == '\"' && current->in_single_quotes == 0)
			current->in_double_quotes = !current->in_double_quotes;
		else if (current->value[i] == '\'' && current->in_double_quotes == 0)
			current->in_single_quotes = !current->in_single_quotes;
		else if (current->in_double_quotes == 1)
			n_bytes++;
		else if (current->in_single_quotes == 1)
			n_bytes++;
		else
			n_bytes++;
		i++;
	}
	return (n_bytes);
}

static char	*remove_quotes_from_token(t_token *token)
{
	size_t	i;
	size_t	j;
	char	*new_value;

	j = 0;
	i = 0;
	new_value = malloc(sizeof(char) * (size_counter_without_quotes(token) + 1));
	if (!new_value)
		return (NULL);
	while (token->value[i])
	{
		if (token->value[i] == '"' && token->in_single_quotes == 0)
			token->in_double_quotes = !token->in_double_quotes;
		else if (token->value[i] == '\'' && token->in_double_quotes == 0)
			token->in_single_quotes = !token->in_single_quotes;
		else
		{
			new_value[j] = token->value[i];
			j++;
		}
		i++;
	}
	new_value[j] = '\0';
	return (new_value);
}

static bool	check_if_remove(char *token)
{
	int		i;

	i = 0;
	if (!token)
		return (false);
	while (token[i] != '\0')
	{
		if (token[i] == '\'' || token[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	delete_quotes(t_token **list, t_shell *shell)
{
	t_token		*current;
	t_token		*next;
	char		*new_value;

	(void)shell;
	if (!list || !*list)
		return (-1);
	current = *list;
	while (current)
	{
		next = current->next;
		if (check_if_remove(current->value) == true)
		{
			new_value = remove_quotes_from_token(current);
			if (!new_value)
				return (-1);
			free(current->value);
			current->value = new_value;
			current->in_single_quotes = 0;
			current->in_double_quotes = 0;
		}
		current = next;
	}
	return (0);
}
