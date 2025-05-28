/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:18 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/28 10:27:35 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	free_struct(t_shell *shell)
{
	free_env(shell->env);
	free(shell);
}

void	free_tokens(t_token **list)
{
	t_token	*next;

	if (!list)
		return ;
	while (*list)
	{
		next = (*list)->next;
		if ((*list)->value)
		{
			free((*list)->value);
			(*list)->value = NULL;
		}
		free((*list));
		(*list) = next;
	}
}
