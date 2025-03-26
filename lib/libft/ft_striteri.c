/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:20:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/04 16:24:05 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void fttoupper(unsigned int i, char *c)
{   
    printf("Index: %d  Caracter: %c\n", i, *c);
}

int main(void)
{
    char str[] = "hello world";

    ft_striteri(str, &fttoupper);
    return (0);
}
*/
