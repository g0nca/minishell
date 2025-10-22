/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:17:05 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/22 11:26:06 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_direct_path_shell_error(char *path, t_shell *shell)
{
	struct stat	path_stat;

	if (ft_strchr(path, '/') == NULL)
	{
		shell_error(shell, path, 1, false);
		return (1);
	}
	if (stat(path, &path_stat) == -1)
	{
		shell_error(shell, path, 2, false);
		return (1);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		shell_error(shell, path, 5, false);
		return (1);
	}
	if (access(path, X_OK) == -1)
	{
		shell_error(shell, path, 20, false);
		return (1);
	}
	return (0);
}
