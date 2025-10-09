/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:08:39 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/09 12:41:16 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	shell->last_exit_status = EXIT_SUCCESS;
}
