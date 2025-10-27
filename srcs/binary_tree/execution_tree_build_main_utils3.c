/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_build_main_utils3.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:33:30 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/27 11:56:22 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_heredoc_delimiters_counter(t_exec_node *cmd)
{
	int		count;

	count = 0;
	if (cmd->heredoc_delimiters)
	{
		while (cmd->heredoc_delimiters[count])
			count++;
	}
	return (count);
}

static char	**allocate_new_delimiters_array(int count)
{
	char	**new_array;

	new_array = malloc(sizeof(char *) * (count + 2));
	return (new_array);
}

static int	copy_old_delimiters(char **new_array, char **old_array, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		new_array[i] = old_array[i];
		i++;
	}
	return (i);
}

static int	add_new_delimiter(char **new_array, int count, char *delimiter)
{
	new_array[count] = ft_strdup(delimiter);
	if (!new_array[count])
		return (-1);
	new_array[count + 1] = NULL;
	return (0);
}

int	update_delimiters_array(t_exec_node *cmd, char *new_delimiter)
{
	char	**new_array;
	int		count;

	count = handle_heredoc_delimiters_counter(cmd);
	new_array = allocate_new_delimiters_array(count);
	if (!new_array)
		return (-1);
	copy_old_delimiters(new_array, cmd->heredoc_delimiters, count);
	if (add_new_delimiter(new_array, count, new_delimiter) == -1)
	{
		free(new_array);
		return (-1);
	}
	if (cmd->heredoc_delimiters)
		free(cmd->heredoc_delimiters);
	cmd->heredoc_delimiters = new_array;
	return (0);
}
