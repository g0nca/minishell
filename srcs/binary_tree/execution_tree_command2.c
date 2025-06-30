/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_command1.c                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:55:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:00:51 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*create_and_link_token(t_token **current,
		char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = create_token(value, type);
	if (!new_token)
		return (NULL);
	(*current)->next = new_token;
	new_token->prev = *current;
	*current = new_token;
	return (new_token);
}

static t_token	*create_command_token(char *cmd)
{
	return (create_token(cmd, TOKEN_CMD));
}

t_token	*create_token_chain(char **cmd)
{
	t_token	*cmd_token;
	t_token	*current;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	cmd_token = create_command_token(cmd[0]);
	if (!cmd_token)
		return (NULL);
	current = cmd_token;
	i = 1;
	while (cmd[i])
	{
		if (!create_and_link_token(&current, cmd[i], TOKEN_WORD))
		{
			free_tokens(&cmd_token);
			return (NULL);
		}
		i++;
	}
	return (cmd_token);
}
