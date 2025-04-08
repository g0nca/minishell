/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:14:31 by andrade           #+#    #+#             */
/*   Updated: 2025/04/08 10:54:27 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_error(int error, char *str)
{
	if (error == 1)
		ft_printf_fd(STDERR_FILENO, "%s: command not found\n", str);
	else if (error == 2)
		ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", str);
	else if (error == 3)
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
	else if (error == 4)
		ft_printf_fd(STDERR_FILENO, "minishell: ambiguous redirect\n", str);
	else if (error == 5)
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", str);
	else if (error == 6)
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Not a directory\n", str);
	else if (error == 7)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `%s'\n", str);
	else if (error == 8)
		ft_printf_fd(STDERR_FILENO, "minishell: exit: %s: numeric argument required\n", str);
	else if (error == 9)
		ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
	else if (error == 10)
		ft_printf_fd(STDERR_FILENO, "minishell: `%s': not a valid identifier\n", str);
	else if (error == 11)
		ft_printf_fd(STDERR_FILENO, "minishell: %s: filename argument required\n", str);
	else
		ft_printf_fd(STDERR_FILENO, "%s\n", str);
}