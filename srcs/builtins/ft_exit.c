/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:59:40 by joaomart          #+#    #+#             */
/*   Updated: 2025/09/16 12:07:20 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == '-')
		i++;
	if (!str[i])
		return (1);
	while (str[i] == '+')
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

static char	*get_token_value(t_token *args, int index)
{
	int	i;

	i = 0;
	while (args && i < index)
	{
		args = args->next;
		i++;
	}
	if (args)
		return (args->value);
	else
		return (NULL);
}

static int	normalize_exit_code(long long code)
{
	if (code >= 0)
		return (code % 256);
	else
		return (256 + (code % 256));
}

static void	is_not_number(t_shell *shell, char *arg1)
{
	ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", arg1);
	free_struct(shell);
	exit(2);
}

static size_t	ft_strlen_exit(const char *s)
{
	int	i;
	int	signals;

	signals = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '-' || s[i] == '+')
			signals++;
		i++;
	}
	return (i - signals);
}

void	ft_exit(t_shell *shell, t_token *args)
{
	long long	exit_code;
	char		*arg1;
	char		*arg2;

	exit_code = 0;
	arg1 = get_token_value(args, 1);
	arg2 = get_token_value(args, 2);
	ft_printf_fd(1, "exit\n");
	if (arg1 && arg2)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		exit(1);
	}
	if (arg1)
	{
		if (ft_strlen_exit(arg1) <= 19)
		{
			if (ft_strcmp(arg1, "9223372036854775808") == 0 || !is_valid_number(arg1))
				is_not_number(shell, arg1);
			else
				exit_code = normalize_exit_code(ft_atol(arg1));
		}
	}
	free_struct(shell);
	exit((int)exit_code);
}
