#include "../../inc/minishell.h"

// Manual implementation of WIFEXITED - checks if process exited normally
int manual_wifexited(int status)
{
    return ((status & 0x7f) == 0);
}

// Manual implementation of WEXITSTATUS - extracts exit status
int manual_wexitstatus(int status)
{
    return ((status & 0xff00) >> 8);
}

void setup_pipe_left_child(int *pipe_fd, t_exec_node *node, t_shell *shell)
{
    close(pipe_fd[0]);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
    execute_tree(node->left, shell);
    exit(shell->last_exit_status);
}

void setup_pipe_right_child(int *pipe_fd, t_exec_node *node, t_shell *shell)
{
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
    execute_tree(node->right, shell);
    exit(shell->last_exit_status);
}

void handle_pipe_parent(int *pipe_fd, pid_t left_pid, pid_t right_pid, t_shell *shell)
{
    int status;

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(left_pid, &status, 0);
    waitpid(right_pid, &status, 0);
    
    if (manual_wifexited(status))
        shell->last_exit_status = manual_wexitstatus(status);
    else
        shell->last_exit_status = 1;
}