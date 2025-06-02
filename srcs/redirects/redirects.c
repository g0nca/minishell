/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:55:23 by andrade           #+#    #+#             */
/*   Updated: 2025/06/02 15:58:16 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_token_redir_in(t_token *current)
{
	int		fd;
	char	*filename;

	// Skip to the filename token (should be the next token after <)
	if (current->next && current->next->value)
		filename = current->next->value;
	else
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}

	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}

	close(fd);
	return (0);
}

int	ft_token_redir_out(t_token *current)
{
	int		fd;
	char	*filename;

	// Skip to the filename token (should be the next token after >)
	if (current->next && current->next->value)
		filename = current->next->value;
	else
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}

	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}

	close(fd);
	return (0);
}

int	ft_token_append(t_token *current)
{
	int		fd;
	char	*filename;

	// Skip to the filename token (should be the next token after >>)
	if (current->next && current->next->value)
		filename = current->next->value;
	else
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (1);
	}

	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}

	close(fd);
	return (0);
}

int	setup_redirections(t_token *token)
{
	t_token	*current;
	int		result;

	current = token;
	result = 0;

	while (current && result == 0)
	{
		if (current->type == TOKEN_REDIR_IN)
			result = ft_token_redir_in(current);
		else if (current->type == TOKEN_REDIR_OUT)
			result = ft_token_redir_out(current);
		else if (current->type == TOKEN_APPEND)
			result = ft_token_append(current);

		current = current->next;
	}

	return (result);
}

int	ft_std_close(int stdin_backup, int stdout_backup)
{
	close(stdin_backup);
	close(stdout_backup);
	return (1);
}
