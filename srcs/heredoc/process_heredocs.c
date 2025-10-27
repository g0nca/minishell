/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:13:29 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/27 11:43:50 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cleanup_last_heredoc_in_node(t_exec_node *node)
{
	if (node->heredoc)
	{
		unlink(node->heredoc);
		free(node->heredoc);
		node->heredoc = NULL;
	}
}

static int	process_heredoc_ctrl_d(t_exec_node *node, char *heredoc_file)
{
	if (!heredoc_file)
	{
		if (node->heredoc)
		{
			unlink(node->heredoc);
			free(node->heredoc);
			node->heredoc = NULL;
		}
		return (-1);
	}
	return (0);
}

static int	process_heredoc_ctrl_c(t_exec_node *node, char *heredoc_file)
{
	if (!heredoc_file && g_exit_status == 130)
	{
		if (node->heredoc)
		{
			unlink(node->heredoc);
			free(node->heredoc);
			node->heredoc = NULL;
		}
		return (-1);
	}
	return (0);
}

static int	process_all_heredocs_one_commad(t_exec_node *node, t_shell *shell)
{
	char	*heredoc_file;
	int		i;

	i = 0;
	while (node->heredoc_delimiters[i])
	{
		heredoc_file = create_heredoc(node->heredoc_delimiters[i], shell);
		if (process_heredoc_ctrl_c(node, heredoc_file) == -1)
			return (-1);
		if (process_heredoc_ctrl_d(node, heredoc_file) == -1)
			return (-1);
		cleanup_last_heredoc_in_node(node);
		node->heredoc = heredoc_file;
		i++;
	}
	return (0);
}

int	process_heredocs_in_tree(t_exec_node *node, t_shell *shell)
{
	int		i;

	if (!node)
		return (0);
	if (node->left && process_heredocs_in_tree(node->left, shell) != 0)
		return (-1);
	if (node->right && process_heredocs_in_tree(node->right, shell) != 0)
		return (-1);
	if (node->heredoc_delimiters)
	{
		if (process_all_heredocs_one_commad(node, shell) == -1)
			return (-1);
		i = 0;
		while (node->heredoc_delimiters[i])
		{
			free(node->heredoc_delimiters[i]);
			i++;
		}
		free(node->heredoc_delimiters);
		node->heredoc_delimiters = NULL;
	}
	return (0);
}
