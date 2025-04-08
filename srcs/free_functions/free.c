/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:18 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/03 13:16:29 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// free the copy of enviroment variables and the pointer
void free_env(char **env)
{
    int i;

    i = 0;
    if (!env)
        return ;
    while (env[i])
        free(env[i++]);
    free(env);
}
// free the struct of t_shell
void    free_struct(t_shell *shell)
{
    free_env(shell->env);
    free(shell);
}
