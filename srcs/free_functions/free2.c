/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:19:36 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/22 15:25:27 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_sorted_env(int i, char **sorted_env)
{
	while (i > 0)
		free(sorted_env[--i]);
	free(sorted_env);
}
