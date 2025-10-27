/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:53:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/27 13:14:45 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_path_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static void	handle_direct_path(char **args, t_shell *shell)
{
	char		*path;

	path = args[0];
	if (handle_direct_path_shell_error(path, shell) == 1)
		return ;
	execve(path, args, shell->env);
	shell_error(shell, path, 3, false);
}

void	handle_env_path_execution(char **args, t_shell *shell)
{
	char	*path_env;
	int		result;

	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
		execve(args[0], args, shell->env);
	path_env = get_path_env(shell->env);
	if (!path_env)
		shell_error(shell, args[0], 1, false);
	result = try_paths(args, shell, path_env);
	if (result == 0)
		handle_direct_path(args, shell);
	else
		return ;
}

int	ft_backup_stdio(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
		return (-1);
	else
		return (0);
}

void	ft_restore_stdio(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
