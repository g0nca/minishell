/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:49:18 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/05 13:05:03 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
/*
void    print_list(t_list *lst)
{
        t_list *temp = lst;
        while(temp)
        {
                printf("%s -> ", (char *)temp->content);
                temp = temp->next;
        }
        printf("NULL\n");
}

int     main(void)
{
        t_list  *head = ft_lstnew("Primeiro Elemento");

        t_list  *novo1 = ft_lstnew("Novo Elemento 1");
        t_list  *novo2 = ft_lstnew("Novo Elemento 2");

        printf("Lista Original\n");
        print_list(head);

        ft_lstadd_front(&head, novo1);
        ft_lstadd_front(&head, novo2);

        printf("\nLista apoes adicionar novos elementos no inicio:\n");
        print_list(head);

	printf("Tamanho da Lista:%d\n", ft_lstsize(head));
        return (0);
}
*/
