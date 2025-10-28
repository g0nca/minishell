/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/28 11:18:07 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status = 0;

static void	handle_exit(t_shell *shell, char *line)
{
	int	exit_status;

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
	}
	free_execution_tree(tree, 1);
	tree = NULL;
	shell->tree = NULL;
	free_tokens(&token);
	token = NULL;
	return (0);
}

/* void	print_tokens(t_token *list, t_shell *shell)
{
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
