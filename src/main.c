/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/03 16:06:33 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int     main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_shell *shell;
    char    *line;
    
    shell = init_shell(ac, av, envp);
    while (shell->running)
    {
        line = readline("minishell$");
        if (!line)
            break;
        if (*line)
            add_history(line);
        printf("N:%d\n", parse_line(line));
        if (exit_program(line, shell) == 0)
            return (0);
        print_envp(line, shell);
        printf("%s\n", line);
        free(line);
    }
    return (0);
}

//  FUNCOES AUXILIARES -- APAGAR DEPOIS
void    print_envp(char *line, t_shell *shell)
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
}
int    exit_program(char *line, t_shell *shell)
{
    if (ft_strcmp(line, "exit") == 0)
    {
        shell->running = 0;
        printf("A sair");
        free_struct(shell);
        free(line);
        return (0);
    }
    return (1);
}
