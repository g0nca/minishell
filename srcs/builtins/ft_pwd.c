/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:02 by joaomart          #+#    #+#             */
/*   Updated: 2025/07/07 11:10:57 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = cd_getenv(shell, "PWD");
	if (pwd)
	{
		ft_printf_fd(1, "%s\n", pwd);
		shell->last_exit_status = EXIT_SUCCESS;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		shell->last_exit_status = EXIT_FAILURE;
		shell_error(shell, "PWD Error", 0, false);
		return ;
	}
	ft_printf_fd(1, "%s\n", pwd);
	free(pwd);
	shell->last_exit_status = EXIT_SUCCESS;
}
