/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/03 10:53:37 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char **copy_env(char **envp)
{
    int i, count = 0;
    char **env_copy;

    while (envp[count])
        count++;
    env_copy = malloc(sizeof(char *) * (count + 1));
    if (!env_copy)
        return NULL;
    for (i = 0; i < count; i++)
        env_copy[i] = ft_strdup(envp[i]);
    env_copy[i] = NULL;
    return env_copy;
}

int     main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_shell shell;
    char    *line;

    shell.env = copy_env(envp);
    shell.last_exit_status = 0;
    shell.running = 1;

    while (shell.running)
    {
        line = readline("minishell$");
        if (!line)
            break;
        if (*line)
            add_history(line);
        else
            printf("%s\n", line);
        free(line);
    }
    free_env(shell.env);
    return (0);
}

