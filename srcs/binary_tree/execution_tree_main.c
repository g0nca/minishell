#include "../../inc/minishell.h"

void handle_child_process(t_exec_node *node, t_shell *shell)
{
    execute_tree(node, shell);
    exit(shell->last_exit_status);
}

void handle_parent_process(pid_t pid, t_shell *shell)
{
    int status;

    waitpid(pid, &status, 0);
    if (manual_wifexited(status))
        shell->last_exit_status = manual_wexitstatus(status);
    else
        shell->last_exit_status = 1;
}

// Main execution function that should be called from your shell
void execute_command_tree(t_exec_node *node, t_shell *shell)
{
    pid_t pid;

    if (!node)
        return;
    if (node->type == NODE_COMMAND && node->fd_in == -1 && node->fd_out == -1)// For simple commands without pipes, execute directly in main process
    {
        execute_tree(node, shell);
        return ;
    }
    pid = fork();// For pipes and redirections, fork and execute
    if (pid == -1)
    {
        perror("fork");
        shell->last_exit_status = 1;
        return ;
    }
    if (pid == 0)
        handle_child_process(node, shell);
    else
        handle_parent_process(pid, shell);
}