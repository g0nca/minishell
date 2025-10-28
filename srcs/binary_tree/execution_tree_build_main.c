/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:49:35 by ggomes-v          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/09 09:54:46 by ggomes-v         ###   ########.fr       */
=======
/*   Updated: 2025/05/29 10:51:38 by ggomes-v         ###   ########.fr       */
>>>>>>> PIPES
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

<<<<<<< HEAD
t_exec_node	*build_execution_tree(t_token *start, t_token *end, t_shell *shell)
{
=======
t_exec_node	*build_execution_tree(t_token *start, t_token *end)
{
	t_exec_node	*redirect_node;
>>>>>>> PIPES
	t_token		*last_pipe;

	if (!start || start == end)
		return (NULL);
	last_pipe = find_last_pipe(start, end);
	if (last_pipe)
<<<<<<< HEAD
		return (create_pipe_node(start, last_pipe, end, shell));
	return (wrap_with_redirects(start, end, shell));
}

static void	free_heredoc_delimiters(char **heredoc_delimiters)
{
	int	i;

	if (!heredoc_delimiters)
		return ;
	i = 0;
	while (heredoc_delimiters[i])
		free(heredoc_delimiters[i++]);
	free(heredoc_delimiters);
}

static void	free_node_simple(t_exec_node *node)
{
	free_cmd(node->cmd);
	free_heredoc_delimiters(node->heredoc_delimiters);
	free(node);
}

static void	free_node_resources(t_exec_node *node)
{
	free_cmd(node->cmd);
	if (node->heredoc)
	{
		free(node->heredoc);
		node->heredoc = NULL;
	}
	free_heredoc_delimiters(node->heredoc_delimiters);
=======
		return (create_pipe_node(start, last_pipe, end));
	redirect_node = find_and_create_redirect_node(start, end);
	if (redirect_node)
		return (redirect_node);
	return (create_command_node(start, end));
}

void	free_execution_tree(t_exec_node *node)
{
	if (!node)
		return ;
	free_execution_tree(node->left);
	free_execution_tree(node->right);
	free_cmd(node->cmd);
>>>>>>> PIPES
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->fd_out != -1)
		close(node->fd_out);
<<<<<<< HEAD
}

void	free_execution_tree(t_exec_node *node, int flag)
{
	if (!node)
		return ;
	if (flag == 0)
	{
		free_node_simple(node);
		return ;
	}
	if (node->left)
		free_execution_tree(node->left, 1);
	if (node->right)
		free_execution_tree(node->right, 1);
	free_node_resources(node);
=======
>>>>>>> PIPES
	free(node);
}
