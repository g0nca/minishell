/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:14:31 by andrade           #+#    #+#             */
/*   Updated: 2025/10/27 14:15:20 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_error_extra(int error, char *str, t_shell *shell)
{
	if (error == 8)
	{
		shell->last_exit_status = 1;
		ft_printf_fd(2, "minishell: exit: %s: ", str);
		ft_printf_fd(2, "numeric argument required\n");
	}
	else if (error == 9)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	else if (error == 10)
	{
		ft_printf_fd(2, "minishell: '%s': not a valid identifier\n", str);
		shell->last_exit_status = 1;
	}
	else if (error == 11)
		ft_printf_fd(2, "minishell: %s: filename argument required\n", str);
	else if (error == 15)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n", str);
		shell->last_exit_status = 1;
	}
}

static void	handle_command_errors(int error, char *str, t_shell *shell)
{
	if (error == 1)
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", str);
		shell->last_exit_status = 127;
	}
	else if (error == 2)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n", str);
		shell->last_exit_status = 127;
	}
	else if (error == 3)
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", str);
		shell->last_exit_status = 1;
	}
	else if (error == 16)
	{
		ft_printf_fd(2, "minishell: %s: filename argument required\n", str);
		ft_printf_fd(2, ".: usage: . filename [arguments]\n");
		shell->last_exit_status = 2;
	}
}

static void	handle_misc_errors(int error, char *str, t_shell *shell)
{
	if (error == 4)
		ft_printf_fd(2, "minishell: ambiguous redirect\n");
	else if (error == 5)
	{
		ft_printf_fd(2, "minishell: %s: Is a directory\n", str);
		shell->last_exit_status = 126;
	}
	else if (error == 6)
		ft_printf_fd(2, "minishell: %s: Not a directory\n", str);
	else if (error == 7)
	{
		ft_printf_fd(2, "minishell: ");
		ft_printf_fd(2, "syntax error near unexpected token %s\n", str);
		shell->last_exit_status = 2;
	}
}

void	ft_error(int error, char *str, t_shell *shell)
{
	if ((error >= 1 && error <= 3) || error == 16)
		handle_command_errors(error, str, shell);
	else if (error >= 4 && error <= 7)
		handle_misc_errors(error, str, shell);
	else if (error == 20)
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", str);
		shell->last_exit_status = 126;
	}
	else
		ft_error_extra(error, str, shell);
}

void	shell_error(t_shell *shell, char *str, int error, bool exit_flag)
{
	if (error == 0 || error == 11)
		shell->last_exit_status = 0;
	else
		ft_error(error, str, shell);
	if (exit_flag)
		exit(shell->last_exit_status);
}
