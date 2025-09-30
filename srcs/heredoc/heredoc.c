/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/09/30 14:00:51 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (dup2(fd, 42) == -1)
	{
		close(fd);
		exit(1);
	}
	close(fd);
	read_heredoc_input(delimiter, 42);
	close(42);
	exit(0);
}

static char	*heredoc_parent(int fd, int status, char *filename, t_shell *shell)
{
	t_list	*new_node;

	close(fd);
	restore_main_signals();
	if (my_wifsignaled(status) && my_wtermsig(status) == SIGINT)
	{
		unlink(filename);
		free(filename);
		rl_replace_line("", 0);
		rl_on_new_line();
		return (NULL);
	}
	if (my_wifexited(status) && manual_wexitstatus(status) == 130)
	{
		unlink(filename);
		free(filename);
		rl_replace_line("", 0);
		rl_on_new_line();
		return (NULL);
	}
	new_node = ft_lstnew(filename);
	if (!new_node)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
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
		close(fd);
		waitpid(pid, &status, 0);
		return (heredoc_parent(fd, status, filename, shell));
	}
	close(fd);
	shell->temp_heredoc_path = filename;
	unlink(filename);
	free(filename);
	restore_main_signals();
	return (NULL);
}
