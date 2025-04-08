/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:57:10 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/08 10:43:16 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	ft_puthexa_fd(int fd, unsigned long n, char format)
{
	char	*base;
	int		i;

	if (format == 'x')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	i = 0;
	if (n >= 16)
	{
		i += ft_puthexa_fd(fd, n / 16, format);
		i += ft_puthexa_fd(fd, n % 16, format);
	}
	else if (n < 16)
		i += ft_putchar_fd(fd, base[n]);
	return (i);
}
