/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:40:32 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/05 11:43:18 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
/*
int main()
{
    // Teste 1: Criando um nó com um número inteiro como conteúdo
    int value = 42;
    t_list *node = ft_lstnew(&value);

    if (node != NULL) {
        printf("Teste 1 - Conteúdo do nó: %d\n", *(int *)(node->content));
    } else {
        printf("Teste 1 - Falha ao criar o nó.\n");
    }

    // Teste 2: Criando um nó com uma string como conteúdo
    char *str = "Hello, World!";
    t_list *str_node = ft_lstnew(str);

    if (str_node != NULL) {
        printf("Teste 2 - Conteúdo do nó: %s\n", (char *)(str_node->content));
    } else {
        printf("Teste 2 - Falha ao criar o nó.\n");
    }

    // Liberando memória dos nós criados
    free(node);
    free(str_node);

    return 0;
}
*/
