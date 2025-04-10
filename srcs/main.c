/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/10 11:12:56 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int     main(int ac, char **av, char **envp)
{
    (void) ac;
    (void)av;
    t_shell *shell;
    char    *line;
    t_token *test;

    test = NULL;
    line = NULL;
    shell = init_shell(ac, av, envp);
    while (shell->running)
    {
        line = readline("minishell$ ");
        if (*line)
            add_history(line);
        if (exit_program(line, shell) == 0)
            return (0);
        if (line != NULL && *line)
        {
            main_auxiliar(line, shell, test);
        }
        free(line);
    }
    return (0);
}
int     main_auxiliar(char *line, t_shell *shell, t_token *test)
{
    print_envp(line, shell);
    test = tokenizer(line);
    if (test)
    {
        verify_token(test, shell);
        print_tokens(test);
    }
    free_tokens(test);
    test = NULL;
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
void print_tokens(t_token *list)
{
    if (!list)
        return;

    int i = 0;
    t_token *current = list;

    printf("\n------------------------------------------------\n");
    while (current)
    {
        printf("token[%d] (%d): %s\n", i, current->type, current->value);
        current = current->next;
        i++;
    }
}
