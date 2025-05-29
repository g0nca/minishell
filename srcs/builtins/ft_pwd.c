/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:02 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/29 10:13:24 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

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
