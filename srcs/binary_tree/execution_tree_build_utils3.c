/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_utils3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:17:27 by joaomart          #+#    #+#             */
/*   Updated: 2025/06/30 10:17:27 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HERE_DOC);
}

int	count_arguments(t_token *start, t_token *end)
{
	int		arg_count;
	t_token	*current;

	arg_count = 0;
	current = start;
	while (current && current != end)
	{
		if (current->type == TOKEN_CMD || current->type == TOKEN_WORD)
		{
			arg_count++;
			current = current->next;
		}
		else if (is_redirection_token(current->type))
		{
			current = current->next;
			if (current && current != end && current->type == TOKEN_WORD)
				current = current->next;
		}
		else if (current->type == TOKEN_PIPE)
			break ;
		else
			current = current->next;
	}
	return (arg_count);
}

char	**allocate_command_array(int arg_count)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	handle_command_token(t_exec_node *node, t_token *current, int *i)
{
	node->cmd[*i] = ft_strdup(current->value);
	if (!node->cmd[*i])
	{
		while (--(*i) >= 0)
			free(node->cmd[*i]);
		return (-1);
	}
	if (current->type == TOKEN_CMD)
		node->type = NODE_COMMAND;
	else if (current->type == TOKEN_REDIR_IN)
		node->type = NODE_REDIRECT_IN;
	else if (current->type == TOKEN_REDIR_OUT)
		node->type = NODE_REDIRECT_OUT;
	else if (current->type == TOKEN_APPEND)
		node->type = NODE_REDIRECT_APPEND;
	(*i)++;
	return (0);
}

void	skip_redirection_token(t_token **current, t_token *end)
{
	*current = (*current)->next;
	if (*current && *current != end)
		*current = (*current)->next;
}
