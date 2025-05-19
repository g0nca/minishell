/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:47:08 by andrade           #+#    #+#             */
/*   Updated: 2025/05/19 10:33:01 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_backup_stdio(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	return (*stdin_backup >= 0 && *stdout_backup >= 0);
}

void	ft_restore_stdio(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	ft_execute_builtin(t_token *token, t_shell *shell, int stdin_backup, int stdout_backup)
{
	if (setup_redirections(token) == 0)
	{
		run_builtin(token, shell);
		ft_restore_stdio(stdin_backup, stdout_backup);
	}
}

void	ft_execute_external(t_token *token, t_shell *shell)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return;
	}
	else if (pid == 0)
	{
		setup_redirections(token);
		execute_external_command(token, shell);
		exit(EXIT_FAILURE);
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