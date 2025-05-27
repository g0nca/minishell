/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:11:17 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/27 15:53:01 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env(char **env, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	**allocate_and_copy_env(t_shell *shell, int *count)
{
	char	**copy;
	int		i;

	*count = env_count(shell->env);
	copy = malloc(sizeof(char *) * (*count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		if (shell->env[i] == NULL)
		{
			printf("Warning: NULL environment entry at index %d\n", i);
			break ;
		}
		copy[i] = ft_strdup(shell->env[i]);
		if (!copy[i])
		{
			free_sorted_env(i, copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**copy_and_sort_env(t_shell *shell, int *count)
{
	char	**sorted_env;

	sorted_env = allocate_and_copy_env(shell, count);
	if (!sorted_env)
		return (NULL);
	sort_env(sorted_env, *count);
	return (sorted_env);
}
