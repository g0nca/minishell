/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/09/22 12:33:38 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

static void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static void	restore_main_signals(void)
{
	setup_signals();
}

static int	read_heredoc_input(const char *delimiter, int fd)
{
	char	*line;
	int		delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	setup_heredoc_signals();
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

static char	*heredoc_child(const char *delimiter, int fd)
{
	read_heredoc_input(delimiter, fd);
	close(fd);
	exit(0);
}

static char	*heredoc_parent(int fd, int status, char *filename, t_shell *shell)
{
	t_list	*new_node;

	close(fd);
	restore_main_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(filename);
		free(filename);
		rl_replace_line("", 0);
		rl_on_new_line();
		return (NULL);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		unlink(filename);
		free(filename);
		rl_replace_line("", 0);
		rl_on_new_line();
		return (NULL);
	}
	new_node = ft_lstnew(filename);
	ft_lstadd_back(&shell->heredoc_files, new_node);
	return (filename);
}

char	*create_heredoc(const char *delimiter, t_shell *shell)
{
	int		fd;
	char	*filename;
	pid_t	pid;
	int		status;

	fd = create_temp_file(&filename);
	if (fd < 0)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_child(delimiter, fd);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (heredoc_parent(fd, status, filename, shell));
	}
	close(fd);
	free(filename);
	restore_main_signals();
	return (NULL);
}
