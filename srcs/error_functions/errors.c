/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:14:31 by andrade           #+#    #+#             */
/*   Updated: 2025/05/29 10:10:54 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_error_extra(int error, char *str)
{
	if (error == 8)
	{
		ft_printf_fd(2, "minishell: exit: %s: ", str);
		ft_printf_fd(2, "numeric argument required\n");
	}
	else if (error == 9)
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
	else if (error == 10)
		ft_printf_fd(2, "minishell: `%s': not a valid identifier\n", str);
	else if (error == 11)
		ft_printf_fd(2, "minishell: %s: filename argument required\n", str);
	else
		ft_printf_fd(2, "%s\n", str);
}

void	ft_error(int error, char *str)
{
	if (error == 1)
		ft_printf_fd(2, "minishell: %s: command not found\n", str);
	else if (error == 2)
		ft_printf_fd(2, "minishell: %s: No such file or directory\n", str);
	else if (error == 3)
		ft_printf_fd(2, "minishell: %s: Permission denied\n", str);
	else if (error == 4)
		ft_printf_fd(2, "minishell: ambiguous redirect\n");
	else if (error == 5)
		ft_printf_fd(2, "minishell: %s: Is a directory\n", str);
	else if (error == 6)
		ft_printf_fd(2, "minishell: %s: Not a directory\n", str);
	else if (error == 7)
	{
		ft_printf_fd(2, "minishell: ");
		ft_printf_fd(2, "syntax error near unexpected token `%s'\n", str);
	}
	else
		ft_error_extra(error, str);
}

void	shell_error(t_shell *shell, char *str, int error, bool exit_flag)
{
	int	status;

	status = shell->last_exit_status;
	if (error == 0)
		shell->last_exit_status = 0;
	else
	{
		shell->last_exit_status = 1;
		ft_error(error, str);
	}
	if (exit_flag)
		exit(status);
}
