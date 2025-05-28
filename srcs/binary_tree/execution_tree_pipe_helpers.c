#include "../../inc/minishell.h"

int create_pipe_and_check(int *pipe_fd)
{
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    return (0);
}

pid_t fork_left_child(int *pipe_fd, t_exec_node *node, t_shell *shell)
{
    pid_t left_pid;

    left_pid = fork();
    if (left_pid == -1)
    {
        perror("fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return (-1);
    }
    if (left_pid == 0)
        setup_pipe_left_child(pipe_fd, node, shell);
    return (left_pid);
}

pid_t fork_right_child(int *pipe_fd, t_exec_node *node, t_shell *shell, pid_t left_pid)
{
    pid_t right_pid;

    right_pid = fork();
    if (right_pid == -1)
    {
        perror("fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        waitpid(left_pid, NULL, 0);
        return (-1);
    }
    if (right_pid == 0)
        setup_pipe_right_child(pipe_fd, node, shell);
    return (right_pid);
}

void execute_pipe_node(t_exec_node *node, t_shell *shell)
{
    int     pipe_fd[2];
    pid_t   left_pid;
    pid_t   right_pid;

    if (create_pipe_and_check(pipe_fd) == -1)
        return ;
    left_pid = fork_left_child(pipe_fd, node, shell);
    if (left_pid == -1)
        return ;
    right_pid = fork_right_child(pipe_fd, node, shell, left_pid);
    if (right_pid == -1)
        return ;
    handle_pipe_parent(pipe_fd, left_pid, right_pid, shell);
}