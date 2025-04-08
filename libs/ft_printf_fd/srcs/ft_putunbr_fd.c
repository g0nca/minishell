/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:00:22 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/08 10:43:03 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	ft_putunbr_fd(int fd, unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr > 9)
		i += ft_putunbr_fd(fd, nbr / 10);
	i += ft_putchar_fd(fd, (nbr % 10) + '0');
	return (i);
}
