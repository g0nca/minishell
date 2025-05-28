#include "../../inc/minishell.h"

void setup_file_descriptors(t_exec_node *node)
{
    if (node->fd_in != -1)
    {
        dup2(node->fd_in, STDIN_FILENO);
        close(node->fd_in);
    }
    if (node->fd_out != -1)
    {
        dup2(node->fd_out, STDOUT_FILENO);
        close(node->fd_out);
    }
}

t_token *create_token_chain(char **cmd)
{
    t_token *cmd_token;
    t_token *current;
    t_token *arg_token;
    int     i;

    cmd_token = create_token(cmd[0], TOKEN_CMD);
    if (!cmd_token)
        return (NULL);    
    current = cmd_token;
    i = 1;
    while(cmd[i])
    {
        arg_token = create_token(cmd[i], TOKEN_WORD);
        if (!arg_token)
        {
            free_tokens(&cmd_token);
            return (NULL);
        }
        current->next = arg_token;
        arg_token->prev = current;
        current = arg_token;
        i++;
    }
    return (cmd_token);
}

void execute_command_node(t_exec_node *node, t_shell *shell)
{
    t_token *cmd_token;

    setup_file_descriptors(node);
    if (node->cmd && node->cmd[0])
    {
        cmd_token = create_token_chain(node->cmd);
        if (!cmd_token)
            exit(EXIT_FAILURE);

        execute_command(cmd_token, shell);
        free_tokens(&cmd_token);
    }
}

void execute_tree(t_exec_node *node, t_shell *shell)
{
    if (!node)
        return ;

    if (node->type == NODE_COMMAND)
        execute_command_node(node, shell);
    else if (node->type == NODE_PIPE)
        execute_pipe_node(node, shell);
    else if (node->type == NODE_REDIRECT_OUT || node->type == NODE_REDIRECT_APPEND)
        execute_output_redirect(node, shell);
    else if (node->type == NODE_REDIRECT_IN)
        execute_input_redirect(node, shell);
}

void free_cmd(char **cmd)
{
    int i;

    i = 0;
    if (!cmd)
        return;

    while (cmd[i])
    {
        free(cmd[i]);
        i++;
    }
    free(cmd);
}