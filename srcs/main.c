/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/27 13:52:19 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_exit_status = 0;

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
			free_struct(shell);  // se tiveres cleanup
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
    t_exec *root;

    if (check_syntax_errors_main(line, shell) == 0)
        token = tokenizer(line, shell);
    if (token)
    {
        expander(&token, shell);
        delete_quotes(&token, shell);
        handle_heredoc(token, shell);
        root = build_execution_tree_safe(token);
        print_tokens(token, shell, 0, root);
        //while (wait(NULL) > 0);
        execute_command(token, shell);
        printf("==========================================================\n");
        print_tokens(token, shell, 1, root);
    }
    free_tokens(&token);
    token = NULL;
    return (0);
}

void print_tokens(t_token *list, t_shell *shell, int i, t_exec *exec_list)
{
    if (!list)
        return;

    if (i == 1)
    {
        t_token *current = list;
        while (current)
        {
            printf("token[%d] (%d): %s\n", i, current->type, current->value);
            //printf("\nType_Quotes : [%d]\nQuotes_Check : [%d]\n", current->type_quotes, current->quotes_check);
            current = current->next;
            i++;
        }
    }
    else if (i == 0)
    {
        t_exec *current = exec_list;

        while (current)
        {
            printf("EXEC_LIST:%s\n", current->token->value);
            //printf("\nType_Quotes : [%d]\nQuotes_Check : [%d]\n", current->type_quotes, current->quotes_check);
            current = current->right;
            i++;
        }
    }
    printf("last_exit_status:%d\n", shell->last_exit_status);
}
/* void print_tokens_without_shell(t_token *list)
{
    if (!list)
        return;

    int i = 0;
    t_token *current = list;
    printf("---------------------------------------------------------\n");
    while (current)
    {
        printf("token[%d] (%d): %s\n", i, current->type, current->value);
        current = current->next;
        i++;
    }
    printf("---------------------------------------------------------\n");
} */
