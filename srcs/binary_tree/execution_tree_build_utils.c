/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:17:21 by joaomart          #+#    #+#             */
/*   Updated: 2025/06/30 10:17:21 by joaomart         ###   ########.fr       */
=======
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:51:54 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 10:55:28 by ggomes-v         ###   ########.fr       */
>>>>>>> PIPES
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*find_last_pipe(t_token *start, t_token *end)
{
	t_token		*curr;
	t_token		*last_pipe;

	curr = start;
	last_pipe = NULL;
	while (curr && curr != end)
	{
		if (curr->type == TOKEN_PIPE)
			last_pipe = curr;
		curr = curr->next;
	}
	return (last_pipe);
}

<<<<<<< HEAD
t_exec_node	*create_pipe_node(t_token *start, t_token *last_pipe,
		t_token *end, t_shell *shell)
=======
t_exec_node	*create_pipe_node(t_token *start, t_token *last_pipe, t_token *end)
>>>>>>> PIPES
{
	t_exec_node	*node;

	node = malloc(sizeof(t_exec_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->cmd = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
<<<<<<< HEAD
	node->input_file = NULL;
	node->output_file = NULL;
	node->append_file = NULL;
	node->heredoc = NULL;
	node->heredoc_delimiters = NULL;
	node->last_redir_in = NULL;
	node->last_redir_in_type = 0;
	node->left = build_execution_tree(start, last_pipe, shell);
	node->right = build_execution_tree(last_pipe->next, end, shell);
=======
	node->left = build_execution_tree(start, last_pipe);
	node->right = build_execution_tree(last_pipe->next, end);
>>>>>>> PIPES
	return (node);
}

t_node_type	get_redirect_node_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (NODE_REDIRECT_IN);
	else if (type == TOKEN_REDIR_OUT)
		return (NODE_REDIRECT_OUT);
	else
		return (NODE_REDIRECT_APPEND);
}
<<<<<<< HEAD
=======

t_exec_node	*create_command_node(t_token *start, t_token *end)
{
	t_exec_node	*node;

	node = malloc(sizeof(t_exec_node));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->cmd = tokens_to_argv(start, end);
	node->left = NULL;
	node->right = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	if (!node->cmd || !node->cmd[0])
	{
		free_cmd(node->cmd);
		free(node);
		return (NULL);
	}
	return (node);
}
>>>>>>> PIPES
