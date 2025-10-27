/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/27 11:23:06 by joaomart         ###   ########.fr       */
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
			if (g_exit_status == 130)
				return (130);
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

void	heredoc_child(const char *delimiter, int fd,
		t_shell *shell, char *filename)
{
	int	exit_code;

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
	exit_code = read_heredoc_input(delimiter, 42);
	free(filename);
	close(42);
	free_execution_tree(shell->tree, 1);
	free_tokens(&shell->token);
	free(shell->token);
	free_struct(shell, 1);
	free(shell);
	exit(exit_code);
}

static int	handle_heredoc_interrupt(int status, char *filename, t_shell *shell)
{
	if ((my_wifsignaled(status) && my_wtermsig(status) == SIGINT)
		|| (my_wifexited(status) && manual_wexitstatus(status) == 130))
	{
		unlink(filename);
		free(filename);
		if (my_wifexited(status))
			shell->last_exit_status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		return (1);
	}
	return (0);
}

char	*heredoc_parent(int fd, int status, char *filename, t_shell *shell)
{
	t_list	*new_node;

	close(fd);
	restore_main_signals();
	if (handle_heredoc_interrupt(status, filename, shell))
		return (NULL);
	new_node = ft_lstnew(filename);
	if (!new_node)
	{
		free(filename);
		return (NULL);
	}
	ft_lstadd_back(&shell->heredoc_files, new_node);
	return (filename);
}
