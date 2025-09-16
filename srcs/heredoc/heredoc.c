/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/09/16 15:58:03 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(1);
}

static int	read_heredoc_input(const char *delimiter, int fd)
{
    char	*line;
    int		delimiter_len;

    delimiter_len = ft_strlen(delimiter);
    signal(SIGINT, handle_heredoc_sigint);
    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
        {
            error_heredoc(delimiter);
            break ;
        }
        if (ft_strncmp(line, delimiter, delimiter_len) == 0
            && line[delimiter_len] == '\0')
        {
            free(line);
            break ;
        }
        ft_printf_fd(fd, "%s\n", line);
        free(line);
    }
    return (0);
}

char	*create_heredoc(const char *delimiter, t_shell *shell)
{
    int		fd;
    char	*filename;
    t_list	*new_node;
    pid_t	pid;
    int		status;

    fd = create_temp_file(&filename);
    if (fd < 0)
        return (NULL);
    pid = fork();
    if (pid == 0)
    {
        read_heredoc_input(delimiter, fd);
        close(fd);
        exit(0);
    }
    else if (pid > 0)
    {
        close(fd);
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            unlink(filename);
            free(filename);
            return (NULL);
        }
        new_node = ft_lstnew(filename);
        ft_lstadd_back(&shell->heredoc_files, new_node);
        return (filename);
    }
    else
    {
        close(fd);
        free(filename);
        return (NULL);
    }
}

void	handle_heredoc(t_token *token, t_shell *shell)
{
	if (process_heredoc(token, shell) != 0)
		shell->last_exit_status = 1;
}
