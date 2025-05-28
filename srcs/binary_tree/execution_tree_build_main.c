#include "../../inc/minishell.h"

t_exec_node *build_execution_tree(t_token *start, t_token *end)
{
    t_exec_node *redirect_node;
    t_token *last_pipe;

    if (!start || start == end)
        return NULL;

    last_pipe = find_last_pipe(start, end);// 1. Find pipe (lowest precedence, right associative)
    if (last_pipe)
        return (create_pipe_node(start, last_pipe, end));

    redirect_node = find_and_create_redirect_node(start, end);// 2. Find redirection (higher precedence than pipe)
    if (redirect_node)
        return (redirect_node);

    return (create_command_node(start, end));
}

void free_execution_tree(t_exec_node *node)
{
    if (!node)
        return;

    free_execution_tree(node->left);
    free_execution_tree(node->right);
    free_cmd(node->cmd);

    if (node->fd_in != -1)
        close(node->fd_in);
    if (node->fd_out != -1)
        close(node->fd_out);

    free(node);
}