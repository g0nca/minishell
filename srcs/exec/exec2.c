/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:53:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/30 10:53:22 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_with_full_path(char **args, t_shell *shell)
{
	execve(args[0], args, shell->env);
	perror("minishell: execve");
	free_args(args);
	exit(EXIT_FAILURE);
}

static int	execute_from_path(char *full_path, char **args, t_shell *shell)
{
	execve(full_path, args, shell->env);
	perror("minishell: execve");
	free(full_path);
	free_args(args);
	exit(EXIT_FAILURE);
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
	if (access(full_path, X_OK) == 0)
	{
		result = execute_from_path(full_path, args, shell);
		return (result);
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
		return (perror("ft_strdup"), -1);
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

void	execute_external_command(t_token *token, t_shell *shell)
{
	char	**args;

	args = token_to_args(token);
	if (!args || !args[0])
	{
		free_args(args);
		exit(EXIT_FAILURE);
	}
	if (!handle_absolute_path(args, shell))
		handle_env_path_execution(args, shell);
	free_args(args);
	exit(EXIT_FAILURE);
}
