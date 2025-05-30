/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/30 11:09:18 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	t_shell	*shell;
	char	*line;
	t_token	*token;

	token = NULL;
	line = NULL;
	shell = init_shell(ac, av, envp);
	init_shlvl(shell);
	setup_signals();
	while (shell->running)
	{
		g_exit_status = shell->last_exit_status;
		line = readline("minishell$ ");
		if (line == NULL) // Ctrl-D
		{
			printf("exit\n");
			free_struct(shell); // se tiveres cleanup
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
    t_exec_node *tree;

    tree = NULL;
    if (check_syntax_errors_main(line, shell) == 0)
        token = tokenizer(line, shell);
    if (token)
    {
        expander(&token, shell);
        delete_quotes(&token, shell);
        handle_heredoc(token, shell);
        //tree = build_execution_tree(token, NULL);
        //execute_tree(tree, shell);
        execute_command(token, shell);
        //printf("==========================================================\n");
        //print_tokens(token, shell, 1, tree);
    }
    free_tokens(&token);
    free_execution_tree(tree);
    token = NULL;
    return (0);
}

void print_tokens(t_token *list, t_shell *shell)
{
    if (!list)
        return;
    int i;
    i = 0;
    t_token *current = list;
    while (current)
    {
        printf("token[%d] (%d): %s\n", i, current->type, current->value);
        current = current->next;
        i++;
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
