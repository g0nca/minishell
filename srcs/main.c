/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/16 15:31:28 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int     main(int ac, char **av, char **envp)
{
    (void) ac;
    (void)av;
    t_shell *shell;
    char    *line;
    t_token *token;

    token = NULL;
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
            main_auxiliar(line, shell, token);
        }
        free(line);
    }
    return (0);
}
int     main_auxiliar(char *line, t_shell *shell, t_token *token)
{
    print_envp(line, shell);
    if (check_syntax_errors(line, shell) == 0)
        token = tokenizer(line);
    if (token)
    {
        expander(token, shell);
        verify_token(token, shell);
        print_tokens(token, shell);
    }
    free_tokens(token);
    token = NULL;
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
        animation("Leaving Without Leaks :) ");
        free_struct(shell);
        free(line);
        return (0);
    }
    return (1);
}

void print_tokens(t_token *list, t_shell *shell)
{
    if (!list)
        return;
    
    int i = 0;
    t_token *current = list;

    while (current)
    {
        printf("token[%d] (%d): %s\n", i, current->type, current->value);
        //printf("\nType_Quotes : [%d]\nQuotes_Check : [%d]\n", current->type_quotes, current->quotes_check);
        current = current->next;
        i++;
    }
    printf("last_exit_status:%d\n", shell->last_exit_status);
}

void animation(char *mensagem)
{
    int i;
    printf("\n");
    for (i = 0; mensagem[i] != '\0'; i++) {
        printf("%c", mensagem[i]);
    fflush(stdout);        // força o print imediato
    usleep(100000);        // 0.1 segundos (100ms)
    }
}
