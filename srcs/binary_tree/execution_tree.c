#include "../../inc/minishell.h"

static int is_redirection(t_token_type type)
{
    return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || type == TOKEN_APPEND);
}

static void free_cmd(char **cmd)
{
    if (!cmd)
        return;

    for (int i = 0; cmd[i]; i++)
        free(cmd[i]);
    free(cmd);
}

// Manual implementation of WIFEXITED - checks if process exited normally
static int manual_wifexited(int status)
{
    return ((status & 0x7f) == 0);
}

// Manual implementation of WEXITSTATUS - extracts exit status
static int manual_wexitstatus(int status)
{
    return ((status & 0xff00) >> 8);
}

static void handle_child_process(t_exec_node *node, t_shell *shell)
{
    execute_tree(node, shell);
    exit(shell->last_exit_status);
}

static void handle_parent_process(pid_t pid, t_shell *shell)
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

static void setup_file_descriptors(t_exec_node *node)
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

static t_token *create_token_chain(char **cmd)
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

static void execute_command_node(t_exec_node *node, t_shell *shell)
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

static void setup_pipe_left_child(int *pipe_fd, t_exec_node *node, t_shell *shell)
{
    close(pipe_fd[0]);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
    execute_tree(node->left, shell);
    exit(shell->last_exit_status);
}

static void setup_pipe_right_child(int *pipe_fd, t_exec_node *node, t_shell *shell)
{
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
    execute_tree(node->right, shell);
    exit(shell->last_exit_status);
}

static void handle_pipe_parent(int *pipe_fd, pid_t left_pid, pid_t right_pid, t_shell *shell)
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

static void execute_pipe_node(t_exec_node *node, t_shell *shell)
{
    int     pipe_fd[2];
    pid_t   left_pid;
    pid_t   right_pid;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return ;
    }
    left_pid = fork();
    if (left_pid == -1)
    {
        perror("fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return ;
    }
    if (left_pid == 0)
        setup_pipe_left_child(pipe_fd, node, shell);
    right_pid = fork();
    if (right_pid == -1)
    {
        perror("fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        waitpid(left_pid, NULL, 0);
        return ;
    }
    if (right_pid == 0)
        setup_pipe_right_child(pipe_fd, node, shell);
    handle_pipe_parent(pipe_fd, left_pid, right_pid, shell);
}

static void execute_output_redirect(t_exec_node *node, t_shell *shell)
{
    int flags;
    int fd;
    
    flags = O_WRONLY | O_CREAT | (node->type == NODE_REDIRECT_APPEND ? O_APPEND : O_TRUNC);
    fd = open(node->cmd[0], flags, 0644);
    if (fd < 0)
    {
        perror("open");
        shell->last_exit_status = 1;
        return ;
    }
    if (node->left)
    {
        node->left->fd_out = fd;
        execute_tree(node->left, shell);
    }
    else
        close(fd);
}

static void execute_input_redirect(t_exec_node *node, t_shell *shell)
{
    int fd;

    fd = open(node->cmd[0], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        shell->last_exit_status = 1;
        return ;
    }
    if (node->left)
    {
        node->left->fd_in = fd;
        execute_tree(node->left, shell);
    }
    else
        close(fd);
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

static int count_valid_tokens(t_token *start, t_token *end)
{
    int count;
    t_token *tmp;
    
    tmp = start;
    count = 0;
    while (tmp && tmp != end)
    {
        if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
        {
            if (tmp->next && is_redirection(tmp->next->type))
            {
                tmp = tmp->next->next;
                continue;
            }
            count++;
        }
        tmp = tmp->next;
    }
    return (count);
}

static void fill_argv_array(t_token *start, t_token *end, char **argv, int count)
{
    t_token *tmp = start;
    int i = 0;
    
    while (tmp && tmp != end && i < count)
    {
        if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
        {
            if (tmp->next && is_redirection(tmp->next->type))
            {
                tmp = tmp->next->next;
                continue;
            }
            argv[i] = strdup(tmp->value);
            if (!argv[i])
            {
                for (int j = 0; j < i; j++)
                    free(argv[j]);
                free(argv);
                return ;
            }
            i++;
        }
        tmp = tmp->next;
    }
    argv[i] = NULL;
}

char **tokens_to_argv(t_token *start, t_token *end)
{
    int count;
    char **argv;

    count = count_valid_tokens(start, end);
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);
        
    fill_argv_array(start, end, argv, count);
    return (argv);
}

static t_token *find_last_pipe(t_token *start, t_token *end)
{
    t_token *curr;
    t_token *last_pipe;

    curr = start;
    last_pipe = NULL;
    while (curr && curr != end)
    {
        if (curr->type == TOKEN_PIPE)
            last_pipe = curr;
        curr = curr->next;
    }
    return (last_pipe);
}

static t_exec_node *create_pipe_node(t_token *start, t_token *last_pipe, t_token *end)
{
    t_exec_node *node;

    node = malloc(sizeof(t_exec_node));
    if (!node)
        return (NULL);
        
    node->type = NODE_PIPE;
    node->cmd = NULL;
    node->fd_in = -1;
    node->fd_out = -1;
    node->left = build_execution_tree(start, last_pipe);
    node->right = build_execution_tree(last_pipe->next, end);
    return (node);
}

static t_node_type get_redirect_node_type(t_token_type type)
{
    if (type == TOKEN_REDIR_IN)
        return (NODE_REDIRECT_IN);
    else if (type == TOKEN_REDIR_OUT)
        return (NODE_REDIRECT_OUT);
    else
        return (NODE_REDIRECT_APPEND);
}

static t_exec_node *create_redirect_node(t_token *start, t_token *curr, t_token *end)
{
    t_exec_node *node;

    node = malloc(sizeof(t_exec_node));
    if (!node)
        return NULL;
    (void)end;
    node->type = get_redirect_node_type(curr->type);
    node->cmd = malloc(sizeof(char *) * 2);
    if (!node->cmd)
    {
        free(node);
        return (NULL);
    }
    node->cmd[0] = strdup(curr->next->value);
    node->cmd[1] = NULL;
    node->fd_in = -1;
    node->fd_out = -1;
    node->left = build_execution_tree(start, curr);
    node->right = NULL;
    return (node);
}

static t_exec_node *find_and_create_redirect_node(t_token *start, t_token *end)
{
    t_token *curr;
    
    curr = start;
    while (curr && curr != end && curr->next)
    {
        if (is_redirection(curr->type) && curr->next->type == TOKEN_WORD)
            return (create_redirect_node(start, curr, end));
        curr = curr->next;
    }
    return (NULL);
}

static t_exec_node *create_command_node(t_token *start, t_token *end)
{
    t_exec_node *node;

    node = malloc(sizeof(t_exec_node));
    if (!node)
        return (NULL);
        
    node->type = NODE_COMMAND;
    node->cmd = tokens_to_argv(start, end);
    node->left = NULL;
    node->right = NULL;
    node->fd_in = -1;
    node->fd_out = -1;
    
    if (!node->cmd || !node->cmd[0])
    {
        free_cmd(node->cmd);
        free(node);
        return (NULL);
    }
    return (node);
}

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