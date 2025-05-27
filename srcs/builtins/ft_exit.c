/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:59:40 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/22 16:19:58 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_number(const char *str)
{
	int i = 0;

	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static char *get_token_value(t_token *args, int index)
{
	int i = 0;
	while (args && i < index)
	{
		args = args->next;
		i++;
	}
	return (args ? args->value : NULL);
}

static int normalize_exit_code(long long code)
{
	// Normaliza para o range 0-255 como o bash faz
	if (code >= 0)
		return (code % 256);
	else
		return (256 + (code % 256));
}

static void	is_not_number(t_shell *shell, char *arg1)
{
	ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", arg1);
	shell->last_exit_status = 2;
	free_struct(shell);
	exit(2);
}

void	ft_exit(t_shell *shell, t_token *args)
{
	long long	exit_code;
	char		*arg1;
	char		*arg2;

	arg1 = get_token_value(args, 1);
	arg2 = get_token_value(args, 2);
	ft_printf_fd(1, "exit\n");
	if (arg1 && !is_valid_number(arg1))
		is_not_number(shell, arg1);
	if (arg1 && arg2)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		shell->last_exit_status = 1;
		return;
	}
	if (arg1)
	{
		exit_code = ft_atol(arg1);
		exit_code = normalize_exit_code(exit_code);
	}
	else
		exit_code = shell->last_exit_status;
	g_exit_status = (int)exit_code; // Atualiza a variável global antes de sair
	free_struct(shell);
	exit((int)exit_code);
}
