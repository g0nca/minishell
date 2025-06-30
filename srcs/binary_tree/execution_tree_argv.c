/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:48:30 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 10:49:21 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**tokens_to_argv(t_token *start, t_token *end)
{
	int		count;
	char	**argv;

	count = count_valid_tokens(start, end);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	fill_argv_array(start, end, argv, &count);
	return (argv);
}
