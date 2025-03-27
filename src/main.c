/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/03/27 12:56:59 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int     main(void)
{
    char    *rl;
    t_token tokens;

    while (1)
    {
        rl = readline("minishell$");
        if (!rl)
            break;
        if (*rl)
            add_history(rl);
        if (strcmp(rl, "exit") == 0)
        {
            printf("Limpando...\n");
            rl_clear_history();
            free(rl);
            break;
        }
        printf("%s\n", rl);
        free(rl);
    }
    return (0);
}

