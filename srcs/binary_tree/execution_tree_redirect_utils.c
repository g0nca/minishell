/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_redirect_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:10:37 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 11:12:23 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT || type == TOKEN_APPEND);
}

t_exec_node	*create_redirect_node(t_token *start, t_token *curr, t_token *end)
{
    t_exec_node	*node;

    node = malloc(sizeof(t_exec_node));
    if (!node)
        return (NULL);
    node->type = get_redirect_node_type(curr->type);
    node->cmd = malloc(sizeof(char *) * 2);
    if (!node->cmd)
    {
        free(node);
        return (NULL);
    }
    node->cmd[0] = ft_strdup(curr->next->value);
    node->cmd[1] = NULL;
    node->fd_in = -1;
    node->fd_out = -1;

    // O comando deve ser criado com TODOS os argumentos, menos o operador e o ficheiro
    // Por isso, passa start e end para build_execution_tree, mas...
    // ...garante que a função que constrói o comando ignora o operador e o ficheiro!
    node->left = build_execution_tree_skip_redirect(start, curr, end);

    node->right = NULL;
    return (node);
}

t_exec_node *build_execution_tree_skip_redirect(t_token *start, t_token *redirect, t_token *end)
{
    t_token *current = start;
    t_exec_node *node = NULL;
    t_token *filtered_start = NULL;
    t_token *filtered_end = NULL;

    // Cria uma lista ligada temporária só com os tokens que NÃO são o operador nem o ficheiro
    while (current && current != end)
    {
        if (current == redirect)
        {
            // Salta o operador
            current = current->next;
            // Salta o ficheiro
            if (current && current != end)
                current = current->next;
            continue;
        }
        // Marca o início da lista filtrada
        if (!filtered_start)
            filtered_start = current;
        current = current->next;
    }
    filtered_end = end;

    // Agora cria o nó de comando normalmente
    node = create_command_node(filtered_start, filtered_end);
    return node;
}

t_exec_node	*find_and_create_redirect_node(t_token *start, t_token *end)
{
	t_token	*curr;

	curr = start;
	while (curr && curr != end && curr->next)
	{
		if (is_redirection(curr->type) && curr->next->type == TOKEN_WORD)
			return (create_redirect_node(start, curr, end));
		curr = curr->next;
	}
	return (NULL);
}
