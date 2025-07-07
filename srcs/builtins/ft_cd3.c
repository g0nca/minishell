/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:16:09 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/07/07 11:16:56 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_home(t_shell *shell)
{
	char	*target;

	target = cd_getenv(shell, "HOME");
	if (!target)
		return (shell_error(shell, "HOME not set", 0, false));
	if (chdir(target) != 0)
		return (shell_error(shell, (char *)target, 2, false));
	shell->last_exit_status = EXIT_SUCCESS;
}

void	sucess_cd(char *old_pwd, t_shell *shell)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env_var(shell, "OLDPWD", old_pwd);
		update_env_var(shell, "PWD", new_pwd);
		free(new_pwd);
	}
	else
		shell_error(shell, "getcwd error after changing directory", 0, false);
}
