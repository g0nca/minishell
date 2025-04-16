/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:29:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/16 14:30:21 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_env_value(const char *name, char **envp)
{
    int len;
	int i;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
    while (envp[i]) 
	{
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
		i++;
    }
    return (NULL);
}