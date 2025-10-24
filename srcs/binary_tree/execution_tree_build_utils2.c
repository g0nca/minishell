/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_utils2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:17:27 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/09 09:59:44 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	fill_command_array(t_exec_node *node, t_token *start, t_token *end)
{
	t_token	*current;
	int		i;

	current = start;
	i = 0;
	while (current && current != end)
	{
		if (current->type == TOKEN_CMD || current->type == TOKEN_WORD)
		{
			if (handle_command_token(node, current, &i) == -1)
				return (-1);
			current = current->next;
		}
		else if (is_redirection_token(current->type))
		{
			skip_redirection_token(&current, end);
		}
		else if (current->type == TOKEN_PIPE)
			break ;
		else
			current = current->next;
	}
	node->cmd[i] = NULL;
	return (0);
}

static t_exec_node	*initialize_command_node(void)
{
	t_exec_node	*node;

	node = malloc(sizeof(t_exec_node));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->input_file = NULL;
	node->output_file = NULL;
	node->append_file = NULL;
	node->heredoc = NULL;
	node->heredoc_delimiters = NULL;
	node->last_redir_in = NULL;
	node->last_redir_in_type = 0;
	return (node);
}

t_exec_node	*create_command_node(t_token *start, t_token *end)
{
	t_exec_node	*node;
	int			arg_count;

	if (!start)
		return (NULL);
	node = initialize_command_node();
	if (!node)
		return (NULL);
	arg_count = count_arguments(start, end);
	node->cmd = allocate_command_array(arg_count);
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	if (fill_command_array(node, start, end) == -1)
	{
		free(node->cmd);
		free(node);
		return (NULL);
	}
	return (node);
}
