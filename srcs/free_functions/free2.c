/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:19:36 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/22 10:59:56 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_sorted_env(int i, char **sorted_env)
{
	while (i > 0)
		free(sorted_env[--i]);
	free(sorted_env);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_free(char **str)
{
	if (!str || !*str)
		return ;
	free (*str);
	*str = NULL;
}

void	free_array_ref(char ***cmd)
{
	int	i;

	i = 0;
	if (!cmd || !(*cmd))
		return ;
	while ((*cmd)[i])
	{
		ft_free(&(*cmd)[i]);
		(*cmd)[i] = NULL;
		i++;
	}
	free (*cmd);
	*cmd = NULL;
}
