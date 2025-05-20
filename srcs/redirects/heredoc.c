/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/20 14:40:47 by andrade          ###   ########.fr       */
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

static char	*create_heredoc(const char *delimiter, t_shell *shell)
{
	int fd;
	char *filename;
	t_list *new_node;

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

int	process_heredoc(t_token *token, t_shell *shell)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == TOKEN_HERE_DOC && current->next)
		{
			t_token *heredoc_token = current;
			t_token *delimiter_token = current->next;
			char *filename = create_heredoc(delimiter_token->value, shell);
			if (!filename)
			{
				shell_error(shell, "Failed to create heredoc", 0, false);
				return (1);
			}
			free(heredoc_token->value);
			heredoc_token->value = ft_strdup(filename);
			heredoc_token->type = TOKEN_REDIR_IN;
			remove_token(&token, delimiter_token);
			current = heredoc_token->next;
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