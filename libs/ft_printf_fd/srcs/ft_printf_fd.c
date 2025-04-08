/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:53:38 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/08 10:44:01 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count += ft_print_format_fd(fd, *(++format), args);
		else
		{
			write(fd, format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}