/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:22:24 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/27 11:22:34 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_unlink_filename(char *filename)
{
	unlink(filename);
	free(filename);
}

char	*create_heredoc(const char *delimiter, t_shell *shell)
{
	int		fd;
	int		status;
	pid_t	pid;
	char	*filename;

	g_exit_status = 0;
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
		restore_main_signals();
		return (heredoc_parent(fd, status, filename, shell));
	}
	close(fd);
	shell->temp_heredoc_path = filename;
	free_unlink_filename(filename);
	restore_main_signals();
	return (NULL);
}
