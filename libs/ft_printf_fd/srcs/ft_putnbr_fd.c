/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:51:09 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/08 10:42:45 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	ft_putnbr_fd(int fd, int nbr)
{
	int	i;

	i = 0;
	if (nbr == -2147483648)
	{
		i += ft_putchar_fd(fd, '-');
		i += ft_putchar_fd(fd, '2');
		i += ft_putnbr_fd(fd, 147483648);
	}
	else if (nbr < 0)
	{
		i += ft_putchar_fd(fd, '-');
		i += ft_putnbr_fd(fd, -nbr);
	}
	else if (nbr > 9)
	{
		i += ft_putnbr_fd(fd, nbr / 10);
		i += ft_putnbr_fd(fd, nbr % 10);
	}
	else
		i += ft_putchar_fd(fd, nbr + '0');
	return (i);
}
