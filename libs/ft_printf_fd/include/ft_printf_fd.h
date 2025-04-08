/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:14:38 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/08 15:16:35 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_printf_fd(int fd, const char *format, ...);
int	ft_print_format_fd(int fd, char fmt, va_list ap);
int	ft_putchar_fd(int fd, char c);
int	ft_putstr_fd(int fd, char *str);
int	ft_putnbr_fd(int fd, int nbr);
int	ft_putunbr_fd(int fd, unsigned int nbr);
int	ft_puthexa_fd(int fd, unsigned long n, char format);
int	ft_putptr_fd(int fd, unsigned long ptr);

#endif
