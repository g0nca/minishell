/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:08:05 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/30 14:20:12 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expansion_getpid(t_token *list, t_shell *shell, int i)
{
	pid_t pid;
	(void)list;
	(void)shell;
	(void)i;
	pid = getpid();
	printf("pid:%d\n", pid);
	return (0);
}