/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:39:03 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/30 16:12:14 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Generates a unique temporary filename for the heredoc content
 */
char	*generate_temp_filename(void)
{
	static int	count = 0;
	char		*filename;
	char		*count_str;

	count_str = ft_itoa(count++);
	if (!count_str)
		return (NULL);

	filename = ft_strjoin("/tmp/minishell_heredoc_", count_str);
	free(count_str);

	return (filename);
}

/*
 * Signal handler for heredoc mode
 */
void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130); // Exit child process with status 130
	}
}

/*
 * Setup special signal handlers for heredoc mode
 */
void	setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Read heredoc input in a child process to handle signals properly
 */
int	read_heredoc_input(char *delimiter, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);

	setup_heredoc_signals();

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break; // EOF (Ctrl+D)

		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}

		// Write line to temp file
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}

	close(fd);
	return (0);
}

/*
 * Handle a single heredoc token
 */
int	handle_heredoc(char *delimiter, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*filename;
	int		fd;

	filename = generate_temp_filename();
	if (!filename)
		return (-1);

	pid = fork();
	if (pid == -1)
	{
		free(filename);
		return (-1);
	}

	if (pid == 0)
	{
		// Child process - read heredoc input
		if (read_heredoc_input(delimiter, filename) == -1)
			exit(1);
		exit(0);
	}
	else
	{
		// Parent process - wait for child and handle result
		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			// Child exited with error or was interrupted
			shell->last_exit_status = WEXITSTATUS(status);
			unlink(filename);
			free(filename);
			return (-1);
		}

		// Open the file for reading
		fd = open(filename, O_RDONLY);
		unlink(filename);
		free(filename);

		return (fd);
	}
}

/*
 * Process all heredoc tokens in the command list
 */
int	handle_all_heredocs(t_token *token, t_shell *shell)
{
	t_token	*current;
	int		heredoc_fd;

	current = token;
	while (current)
	{
		if (current->type == TOKEN_HERE_DOC)
		{
			// The next token should contain the delimiter
			if (!current->next || !current->next->value)
				return (-1);

			// Handle the heredoc and get the file descriptor
			heredoc_fd = handle_heredoc(current->next->value, shell);
			if (heredoc_fd == -1)
				return (-1);

			// Store the file descriptor in the delimiter token
			current->next->heredoc_fd = heredoc_fd;
		}
		current = current->next;
	}
	return (0);
}

/*
 * Setup file redirections, including heredocs
 */
int	setup_redirections(t_token *token)
{
	t_token *current;
	int input_fd = STDIN_FILENO;
	int output_fd = STDOUT_FILENO;

	current = token;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
		{
			// Input redirection (<)
			if (!current->next || !current->next->value)
				return (1);

			if (input_fd != STDIN_FILENO)
				close(input_fd);

			input_fd = open(current->next->value, O_RDONLY);
			if (input_fd == -1)
			{
				perror("minishell");
				return (1);
			}
		}
		else if (current->type == TOKEN_REDIR_OUT)
		{
			// Output redirection (>)
			if (!current->next || !current->next->value)
				return (1);

			if (output_fd != STDOUT_FILENO)
				close(output_fd);

			output_fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (output_fd == -1)
			{
				perror("minishell");
				return (1);
			}
		}
		else if (current->type == TOKEN_APPEND)
		{
			// Append redirection (>>)
			if (!current->next || !current->next->value)
				return (1);

			if (output_fd != STDOUT_FILENO)
				close(output_fd);

			output_fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (output_fd == -1)
			{
				perror("minishell");
				return (1);
			}
		}
		else if (current->type == TOKEN_HERE_DOC)
		{
			// Heredoc redirection (<<)
			if (!current->next || !current->next->value)
				return (1);

			if (input_fd != STDIN_FILENO)
				close(input_fd);

			// Use the heredoc file descriptor that was set up earlier
			input_fd = current->next->heredoc_fd;
			if (input_fd == -1)
			{
				fprintf(stderr, "minishell: heredoc failed\n");
				return (1);
			}
		}

		current = current->next;
	}

	// Apply the redirections
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}

	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}

	return (0);
}
