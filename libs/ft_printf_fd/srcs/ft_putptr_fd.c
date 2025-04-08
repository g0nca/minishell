/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:25:10 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/08 10:43:29 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	ft_putptr_fd(int fd, unsigned long ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (ft_putstr_fd(fd, "(nil)"));
	i += ft_putstr_fd(fd, "0x");
	i += ft_puthexa_fd(fd, ptr, 'x');
	return (i);
}
