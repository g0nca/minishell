/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/21 15:04:27 by ggomes-v         ###   ########.fr       */
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

static void	heredoc_child(const char *delimiter, int fd, t_shell *shell, char *filename)
{
	if (dup2(fd, 42) == -1)
	{
		close(fd);
		free_tokens(&shell->token);
		free(shell->token);
		free_struct(shell, 0);
		free(shell);
		exit(1);
	}
	close(fd);
	read_heredoc_input(delimiter, 42);
	free(filename);
	close(42);
	//free_execution_tree(shell->pointer_to_cmd, 0);
	free_tokens(&shell->token);
	free(shell->token);
	free_struct(shell, 0);
	free(shell);
	exit(0);
}

static char	*heredoc_parent(int fd, int status, char *filename, t_shell *shell)
{
	t_list		*new_node;

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
	ft_lstadd_back(&shell->heredoc_files, new_node);
	if (new_node)
		free(new_node);
	return (filename);
}

char	*create_heredoc(const char *delimiter, t_shell *shell)
{
	int		fd;
	int		status;
	pid_t	pid;
	char	*filename;

	fd = create_temp_file(&filename);
	if (fd < 0)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_child(delimiter, fd, shell, filename);
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
