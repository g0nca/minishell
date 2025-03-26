/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:33:08 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/04 16:26:26 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
int main(void)
{
    char buffer[10];
    int i = 0;
    int passed = 1;

    ft_bzero(buffer, sizeof(buffer));

    while (i < sizeof(buffer)) {
        if (buffer[i] != 0) {
            passed = 0;
            break;
        }
        i++;
    }

    if (passed) {
        printf("Teste básico com `char` passou!\n");
    } else {
        printf("Teste básico com `char` falhou.\n");
    }
    return 0;
}
*/
