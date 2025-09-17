/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:46:00 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/17 09:05:01 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_strlen_exit(const char *s)
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

int	too_many_arguments(t_shell *shell)
{
	ft_printf_fd(2, "minishell: exit: too many arguments\n");
	shell->last_exit_status = 1;
	exit(1);
}
