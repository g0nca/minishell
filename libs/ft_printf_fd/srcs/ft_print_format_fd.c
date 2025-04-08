/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:08:58 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/08 10:44:08 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	ft_print_format_fd(int fd, char fmt, va_list ap)
{
	int	count;

	count = 0;
	if (fmt == 'c')
		count += ft_putchar_fd(fd, va_arg(ap, int));
	else if (fmt == 's')
		count += ft_putstr_fd(fd, va_arg(ap, char *));
	else if (fmt == 'd' || fmt == 'i')
		count += ft_putnbr_fd(fd, va_arg(ap, int));
	else if (fmt == 'u')
		count += ft_putunbr_fd(fd, va_arg(ap, unsigned int));
	else if (fmt == 'X' || fmt == 'x')
		count += ft_puthexa_fd(fd, va_arg(ap, unsigned int), fmt);
	else if (fmt == 'p')
		count += ft_putptr_fd(fd, va_arg(ap, unsigned long));
	else if (fmt == '%')
		count += ft_putchar_fd(fd, '%');
	else
		count += write(fd, &fmt, 1);
	va_end(ap);
	return (count);
}
