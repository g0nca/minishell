/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:30:17 by andrade           #+#    #+#             */
/*   Updated: 2025/05/14 10:30:53 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

char **token_to_args(t_token *token)
{
	int		count;
	int		i;
	t_token	*temp;

	count = 0;
	i = 0;
	temp = token;
	while (temp)
	{
		if (temp->type == TOKEN_CMD || temp->type == TOKEN_WORD || 
			temp->type == TOKEN_DOUBLE_QUOTE || temp->type == TOKEN_SIMPLE_QUOTE)
			count++;
		else if (temp->type == TOKEN_REDIR_IN || temp->type == TOKEN_REDIR_OUT || 
				temp->type == TOKEN_APPEND || temp->type == TOKEN_HERE_DOC)
		{
			temp = temp->next;
			if (!temp)
				break;
			continue;
		}
		temp = temp->next;
	}
	
	char **args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	
	temp = token;
	while (temp)
	{
		if (temp->type == TOKEN_CMD || temp->type == TOKEN_WORD || 
			temp->type == TOKEN_DOUBLE_QUOTE || temp->type == TOKEN_SIMPLE_QUOTE)
			args[i++] = ft_strdup(temp->value);
		else if (temp->type == TOKEN_REDIR_IN || temp->type == TOKEN_REDIR_OUT || 
				temp->type == TOKEN_APPEND || temp->type == TOKEN_HERE_DOC)
		{
			temp = temp->next;
			if (!temp)
				break;
			continue;
		}
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

static int setup_redirections(t_token *token)
{
	t_token *current;
	int fd;
	int stdin_backup = dup(STDIN_FILENO);
	int stdout_backup = dup(STDOUT_FILENO);
	int had_error = 0;

	current = token;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
		{
			fd = open(current->value, O_RDONLY);
			if (fd < 0)
			{
				perror("minishell");
				dup2(stdin_backup, STDIN_FILENO);
				dup2(stdout_backup, STDOUT_FILENO);
				close(stdin_backup);
				close(stdout_backup);
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (current->type == TOKEN_REDIR_OUT)
		{
			fd = open(current->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("minishell");
				dup2(stdin_backup, STDIN_FILENO);
				dup2(stdout_backup, STDOUT_FILENO);
				close(stdin_backup);
				close(stdout_backup);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (current->type == TOKEN_APPEND)
		{
			fd = open(current->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("minishell");
				dup2(stdin_backup, STDIN_FILENO);
				dup2(stdout_backup, STDOUT_FILENO);
				close(stdin_backup);
				close(stdout_backup);
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		current = current->next;
	}
	if (had_error)
	{
		close(stdin_backup);
		close(stdout_backup);
		return (1);
	}
	return (0);
}

void execute_command(t_token *token, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		stdin_backup = dup(STDIN_FILENO);
	int		stdout_backup = dup(STDOUT_FILENO);

	if (!token)
		return;
	t_token *temp = token;
	while (temp)
		temp = temp->next;
	if (token && token->type == TOKEN_CMD && is_builtin(token->value))
	{
		if (setup_redirections(token) == 0)
		{
			run_builtin(token, shell);
			dup2(stdin_backup, STDIN_FILENO);
			dup2(stdout_backup, STDOUT_FILENO);
		}
	}
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("minishell: fork");
			return;
		}
		else if (pid == 0)
		{
			// Child process
			setup_redirections(token);
			execute_external_command(token, shell);
			exit(EXIT_FAILURE); // Should not reach here
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				shell->last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->last_exit_status = 128 + WTERMSIG(status);
		}
	}
	close(stdin_backup);
	close(stdout_backup);
	cleanup_heredoc_files(shell);
}