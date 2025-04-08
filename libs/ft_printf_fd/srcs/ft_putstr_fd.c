/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:59:51 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/08 10:42:32 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	ft_putstr_fd(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr_fd(fd, "(null)"));
	while (str[i] != '\0')
	{
		ft_putchar_fd(fd, str[i]);
		i++;
	}
	return (i);
}
