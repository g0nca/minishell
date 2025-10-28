/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2025/10/28 11:18:07 by ggomes-v         ###   ########.fr       */
=======
/*   Updated: 2025/05/29 14:26:12 by ggomes-v         ###   ########.fr       */
>>>>>>> PIPES
=======
/*   Updated: 2025/06/02 16:18:56 by ggomes-v         ###   ########.fr       */
>>>>>>> SolveRedirs
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status = 0;

<<<<<<< HEAD
static void	handle_exit(t_shell *shell, char *line)
{
	int	exit_status;
=======
static void    add_history_function(char *line)
{
    if (*line)
        add_history(line);
}

int     main(int ac, char **av, char **envp)
{
    t_shell *shell;
    char    *line;
    t_token *token;
>>>>>>> PIPES

	if (line == NULL)
	{
		exit_status = shell->last_exit_status;
		printf("exit\n");
		free_struct(shell, 1);
		free(shell);
		exit(exit_status);
	}
}

static void	process_line(char *line, t_shell *shell, t_token *token)
{
	if (*line)
		add_history(line);
	if (line != NULL && *line)
		main_auxiliar(line, shell, token);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*line;
	t_token	*token;

	(void)ac;
	(void)av;
	token = NULL;
	line = NULL;
	shell = init_shell(ac, av, envp);
	init_shlvl(shell);
	setup_signals();
	while (shell->running)
	{
		g_exit_status = shell->last_exit_status;
		line = readline("minishell$ ");
		handle_exit(shell, line);
		process_line(line, shell, token);
		free(line);
	}
	free_struct(shell, 1);
	free(shell);
	ft_printf_fd(1, "exit\n");
	return (g_exit_status);
}

int	main_auxiliar(char *line, t_shell *shell, t_token *token)
{
	t_exec_node	*tree;

	tree = NULL;
	if (check_syntax_errors_main(line, shell) == 0)
		token = tokenizer(line, shell);
	if (token)
	{
		expander(&token, shell);
		delete_quotes(&token, shell);
		shell->token = token;
		tree = build_execution_tree(token, NULL, shell);
		shell->tree = tree;
		if (tree)
		{
			if (process_heredocs_in_tree(tree, shell) == 0)
				execute_tree(tree, shell);
		}
<<<<<<< HEAD
	}
	free_execution_tree(tree, 1);
	tree = NULL;
	shell->tree = NULL;
	free_tokens(&token);
	token = NULL;
	return (0);
=======
        add_history_function(line);
        if (line != NULL && *line)
            main_auxiliar(line, shell, token);
        free(line);
    }
    return (0);
>>>>>>> PIPES
}

/* void	print_tokens(t_token *list, t_shell *shell)
{
<<<<<<< HEAD
	int		i;
	t_token	*current;

	if (!list)
		return ;
	i = 0;
	current = list;
	while (current)
	{
		printf("token[%d] (%d): %s\n", i, current->type, current->value);
		current = current->next;
		i++;
	}
	if (shell)
		printf("last_exit_status:%d\n", shell->last_exit_status);
=======
    t_exec_node *tree;

    tree = NULL;
    if (check_syntax_errors_main(line, shell) == 0)
        token = tokenizer(line, shell);
    if (token)
    {
        expander(&token, shell);
        delete_quotes(&token, shell);
        handle_heredoc(token, shell);
        tree = build_execution_tree(token, NULL);
        execute_tree(tree, shell);
        //execute_command(token, shell);
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
>>>>>>> PIPES
} */
/*
 const char	*node_type_to_str(t_node_type type)
{
	if (type == NODE_COMMAND)
		return "NODE_COMMAND";
	else if (type == NODE_PIPE)
		return "PIPE";
	else if (type == NODE_REDIRECT_IN)
		return "REDIRECT_IN";
	else if (type == NODE_REDIRECT_OUT)
		return "REDIRECT_OUT";
	else if (type == NODE_REDIRECT_APPEND)
		return "REDIRECT_APPEND";
	else if (type == HEREDOC)
		return "HEREDOC";
	return "UNKNOWN";
}

// Função para imprimir a árvore de execução
void	print_exec_tree(t_exec_node *node, int depth)
{
	int	i;

	if (!node)
		return;

	for (i = 0; i < depth; i++)
		printf("  ");

	printf("Node Type: %s\n", node_type_to_str(node->type));

	if (node->cmd)
	{
		for (i = 0; node->cmd[i]; i++)
		{
			int j;
			for (j = 0; j < depth; j++)
				printf("  ");
			printf("  cmd[%d][%s]: %s\n", i,
				node_type_to_str(node->type), node->cmd[i]);
		}
	}

	for (i = 0; i < depth; i++)
		printf("  ");
	printf("  fd_in: %d, fd_out: %d\n", node->fd_in, node->fd_out);

	if (node->left)
	{
		for (i = 0; i < depth; i++)
			printf("  ");
		printf("Left:\n");
		print_exec_tree(node->left, depth + 1);
	}
	if (node->right)
	{
		for (i = 0; i < depth; i++)
			printf("  ");
		printf("Right:\n");
		print_exec_tree(node->right, depth + 1);
	}
}*/
