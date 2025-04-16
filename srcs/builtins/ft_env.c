/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:08:39 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/16 17:13:27 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_shell *shell)
{
	int i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}

/* void	ft_env(char *line, t_shell *shell)
{
	int i = 0;
	if (ft_strcmp(line, "env") == 0)
	{
		while (shell->env[i])
		{
			printf("%s\n", shell->env[i]);
			i++;
		}
	}
} */
