/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/28 10:37:37 by andrade          ###   ########.fr       */
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
		line = readline("> ");
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
	signal(SIGINT, handle_sigint);
	return (0);
}

char	*create_heredoc(const char *delimiter, t_shell *shell)
{
	int		fd;
	char	*filename;
	t_list	*new_node;

	fd = create_temp_file(&filename);
	if (fd < 0)
		return (NULL);
	if (read_heredoc_input(delimiter, fd) != 0)
	{
		close(fd);
		free(filename);
		return (NULL);
	}
	close(fd);
	new_node = ft_lstnew(filename);
	ft_lstadd_back(&shell->heredoc_files, new_node);
	return (filename);
}

void	handle_heredoc(t_token *token, t_shell *shell)
{
	if (process_heredoc(token, shell) != 0)
		shell->last_exit_status = 1;
}
