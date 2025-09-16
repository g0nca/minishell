/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:20:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/16 12:14:32 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status = 0;

static void	handle_exit(t_shell *shell, char *line)
{
	if (line == NULL)
	{
		printf("exit\n");
		free_struct(shell);
		exit(shell->last_exit_status);
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
	return (shell->last_exit_status);
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
		tree = build_execution_tree(token, NULL, shell);
		execute_tree(tree, shell);
	}
	free_tokens(&token);
	free_execution_tree(tree);
	token = NULL;
	return (0);
}

void	print_tokens(t_token *list, t_shell *shell)
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
	printf("last_exit_status:%d\n", shell->last_exit_status);
}
