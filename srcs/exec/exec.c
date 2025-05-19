/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:30:17 by andrade           #+#    #+#             */
/*   Updated: 2025/05/19 10:31:46 by andrade          ###   ########.fr       */
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

char	**token_to_args(t_token *token)
{
	int		count;
	char	**args;
	
	count = count_args(token);
	args = allocate_args(count);
	if (!args)
		return (NULL);
	fill_args(token, args);
	return (args);
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

void	execute_command(t_token *token, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!token || !ft_backup_stdio(&stdin_backup, &stdout_backup))
		return;
	if (token->type == TOKEN_CMD && is_builtin(token->value))
		ft_execute_builtin(token, shell, stdin_backup, stdout_backup);
	else
		ft_execute_external(token, shell);
	cleanup_heredoc_files(shell);
}