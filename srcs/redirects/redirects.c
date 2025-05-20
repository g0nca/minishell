/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:55:23 by andrade           #+#    #+#             */
/*   Updated: 2025/05/20 14:24:23 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_token_redir_in(t_token *current, int stdin_backup, int stdout_backup)
{
	int	fd;
	char	*filename;

	if (ft_strcmp(current->value, "<") == 0 && current->next)
		filename = current->next->value;
	else
		filename = current->value;
	fd = open(filename, O_RDONLY);
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
	return (0);
}

int	ft_token_redir_out(t_token *current, int stdin_backup, int stdout_backup)
{
	int		fd;
	char	*filename;

	if (ft_strcmp(current->value, ">") == 0 && current->next)
		filename = current->next->value;
	else
		filename = current->value;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	return (0);
}

int	ft_token_append(t_token *current, int stdin_backup, int stdout_backup)
{
	int	fd;
	char	*filename;

	if (ft_strcmp(current->value, ">>") == 0 && current->next)
		filename = current->next->value;
	else
		filename = current->value;
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	return (0);
}

int	setup_redirections(t_token *token)
{
	t_token	*current;
	int		stdin_backup;
	int		stdout_backup;
	int		had_error;

	current = token;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	had_error = 0;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
			ft_token_redir_in(current, stdin_backup, stdout_backup);
		else if (current->type == TOKEN_REDIR_OUT)
			ft_token_redir_out(current, stdin_backup, stdout_backup);
		else if (current->type == TOKEN_APPEND)
			ft_token_append(current, stdin_backup, stdout_backup);
		current = current->next;
	}
	if (had_error)
		ft_std_close(stdin_backup, stdout_backup);
	return (0);
}

int	ft_std_close(int stdin_backup, int stdout_backup)
{
	close(stdin_backup);
	close(stdout_backup);
	return (1);
}