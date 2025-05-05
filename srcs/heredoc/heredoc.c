/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/05 20:01:01 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(1);
}

static char	*generate_temp_filename(int i)
{
	char	*num_str;
	char	*filename;

	num_str = ft_itoa(i);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell_heredoc_", num_str);
	free(num_str);
	return (filename);
}

static int	create_temp_file(void)
{
	char	*filename;
	int		fd;
	int		i;

	i = 0;
	while (1)
	{
		filename = generate_temp_filename(i);
		if (!filename)
			return (-1);
		fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
		{
			free(filename);
			return (fd);
		}
		free(filename);
		i++;
	}
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
			ft_printf_fd(STDERR_FILENO,
				"minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
				delimiter);
			break;
		}
		if (ft_strncmp(line, delimiter, delimiter_len) == 0 &&
			line[delimiter_len] == '\0')
		{
			free(line);
			break;
		}
		ft_printf_fd(fd, "%s\n", line);
		free(line);
	}
	signal(SIGINT, handle_sigint);
	return (0);
}

static char	*create_heredoc(const char *delimiter)
{
	int		fd;
	char	*filename;
	int		i;

	fd = create_temp_file();
	if (fd < 0)
		return (NULL);
	if (read_heredoc_input(delimiter, fd) != 0)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	i = 0;
	while (1)
	{
		filename = generate_temp_filename(i);
		if (!filename)
			return (NULL);
		if (access(filename, F_OK) == 0)
			return (filename);
		free(filename);
		i++;
	}
}

static void	remove_token(t_token **head, t_token *to_remove)
{
	t_token	*prev = NULL;
	t_token	*curr = *head;

	while (curr)
	{
		if (curr == to_remove)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	process_heredoc(t_token *token, t_shell *shell)
{
	t_token	*current = token;

	while (current)
	{
		if (current->type == TOKEN_HERE_DOC && current->next)
		{
			t_token *heredoc_token = current;
			t_token *delimiter_token = current->next;

			char *filename = create_heredoc(delimiter_token->value);
			if (!filename)
			{
				shell_error(shell, "Failed to create heredoc", 0, false);
				return (1);
			}

			// Armazenar o caminho no token << antes de removê-lo
			heredoc_token->heredoc_path = filename;

			// Remover ambos os tokens: '<<' e o delimitador
			remove_token(&token, delimiter_token);
			remove_token(&token, heredoc_token);

			current = token; // reset após modificação
			continue;
		}
		current = current->next;
	}
	return (0);
}

void	handle_heredoc(t_token *token, t_shell *shell)
{
	if (process_heredoc(token, shell) != 0)
		shell->last_exit_status = 1;
}