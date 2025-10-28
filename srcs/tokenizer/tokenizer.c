/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:26:14 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/27 13:42:11 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenizer(char *line, t_shell *shell)
{
	t_token		*list;
	int			i;

	if (!line || !*line)
		return (NULL);
	list = malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	init_token_struct_inicial(list);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\0' && list->type != 0)
			break ;
		else if (ft_isspace(line[i]))
			i++;
		else if (line[i])
			process_token(list, line, &i, shell);
	}
	check_command(list, shell);
	return (list);
}

void	add_token(t_token *list, char *val, t_token_type type)
{
	t_token	*new_token;

	if (!list || !val)
		return ;
	new_token = create_token(val, type);
	if (!new_token)
		return ;
	add_token_to_list(list, new_token);
}

t_token	*create_token(char *val, t_token_type type)
{
	t_token	*new_token;

	if (!val)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(val);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token = init_token_struct_new_node(new_token, type);
	return (new_token);
}

void	add_token_to_list(t_token *list, t_token *new_token)
{
	t_token	*last;

	if (!list || !new_token)
		return ;
	if (!list)
		list = new_token;
	else
	{
		last = list;
		while (last->next)
			last = last->next;
		if (last)
		{
			last->next = new_token;
			new_token->prev = last;
		}
		else
			list = new_token;
	}
	list->size++;
}

void	add_final_token(t_token *list, char *joined)
{
	if (!joined)
		return ;
	add_token(list, joined, TOKEN_WORD);
	free(joined);
}
