/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/24 10:27:39 by joaomart         ###   ########.fr       */
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
    setup_signals();
    while (shell->running)
    {
        line = readline("minishell$ ");
        if (line == NULL)  // Ctrl-D
		{
			printf("exit\n");
			free_shell(shell);  // se tiveres cleanup
			exit(0);
		}
        if (*line)
            add_history(line);
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
    if (check_syntax_errors(line, shell) == 0)
        token = tokenizer(line);
    if (token)
    {
        expander(token, shell);
        verify_token(token, shell);
        execute_command(token, shell);
        print_tokens(token, shell);
    }
    free_tokens(token);
    token = NULL;
    return (0);
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
