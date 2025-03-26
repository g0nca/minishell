/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:27:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/04 16:27:06 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc(num * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}
/*
int main(void)
{
    int num_elements = 500;
   
    int *array = (int *)calloc(num_elements, sizeof(int));

    if(array == NULL) 
    {
        printf("Falha na alocação de memória.\n");
        return 1; // Sair do programa com erro
    }

    int i = 0;
   
    while(i < num_elements) 
    {
        printf("array[%d] = %d\n", i, array[i]); // Saída: 0 para todos
        i++;
    }
}
*/
