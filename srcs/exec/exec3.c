/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:22:07 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/14 16:53:39 by andrade          ###   ########.fr       */
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

bool	handle_absolute_path(char **args, t_shell *shell)
{
	if (ft_strchr(args[0], '/'))
	{
		if (access(args[0], F_OK) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", args[0]);
			exit(127);
		}
		else if (access(args[0], X_OK) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", args[0]);
			exit(126);
		}
		exec_with_full_path(args, shell);
		return (true);
	}
	return (false);
}

void	handle_env_path_execution(char **args, t_shell *shell)
{
	char	*path_env;
	int		found;

	path_env = get_path_env(shell->env);
	if (!path_env)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", args[0]);
		exit(127);
	}
	found = try_paths(args, shell, path_env);
	if (found <= 0)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", args[0]);
		exit(127);
	}
	exit(127);
}
