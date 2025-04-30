/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:22:07 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/30 14:50:39 by joaomart         ###   ########.fr       */
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
		if (access(args[0], X_OK) == 0)
			exec_with_full_path(args, shell);
		else
			shell_error(shell, args[0], 1, false);
		return true;
	}
	return false;
}

void	handle_env_path_execution(char **args, t_shell *shell)
{
	char	*path_env;
	int		found;

	path_env = get_path_env(shell->env);
	if (!path_env)
	{
		shell_error(shell, args[0], 1, false);
		return;
	}
	found = try_paths(args, shell, path_env);
	if (found <= 0)
		shell_error(shell, args[0], 1, false);
}
