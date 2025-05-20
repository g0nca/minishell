/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/20 10:21:21 by andrade          ###   ########.fr       */
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

static int	create_temp_file(char **out_filename)
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
			*out_filename = filename;
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

void	cleanup_heredoc_files(t_shell *shell)
{
	t_list *temp;
	while (shell->heredoc_files)
	{
		temp = shell->heredoc_files;
		unlink((char *)temp->content);
		free(temp->content);
		shell->heredoc_files = shell->heredoc_files->next;
		free(temp);
	}
}

void	remove_token(t_token **head, t_token *to_remove)
{
	t_token	*prev;
	t_token	*curr;
	
	prev = NULL;
	curr = *head;
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