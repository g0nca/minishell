/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:30:17 by andrade           #+#    #+#             */
/*   Updated: 2025/10/27 13:03:30 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static int	execute_from_path(char *full_path, char **args, t_shell *shell)
{
	if (access(full_path, X_OK) == 0)
		execve(full_path, args, shell->env);
	free(full_path);
	if (args[0][0] == '.' && args[0][1] == '.')
		shell_error(shell, "..", 1, EXIT_FAILURE);
	else if (args[0][0] == '.')
	{
		shell_error(shell, ".", 16, EXIT_FAILURE);
	}
	return (0);
}

static int	try_path_execution(char *dir, char **args, t_shell *shell)
{
	char	*temp;
	char	*full_path;
	int		result;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (perror("ft_strjoin"), -1);
	full_path = ft_strjoin(temp, args[0]);
	free(temp);
	if (!full_path)
		return (perror("ft_strjoin"), -1);
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK) == 0)
		{
			result = execute_from_path(full_path, args, shell);
			return (result);
		}
	}
	free(full_path);
	return (0);
}

int	try_paths(char **args, t_shell *shell, char *path_env)
{
	char	*path_copy;
	char	*dir;
	int		result;

	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (-1);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		result = try_path_execution(dir, args, shell);
		if (result != 0)
		{
			free(path_copy);
			return (result);
		}
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (0);
}
