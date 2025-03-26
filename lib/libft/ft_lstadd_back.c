/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:38:06 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/06 17:02:31 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*fim;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	fim = ft_lstlast(*lst);
	fim->next = new;
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
        t_list  *novo3 = ft_lstnew("Novo elemento 3");

        printf("Lista Original\n");
        print_list(head);

        ft_lstadd_front(&head, novo1);
        ft_lstadd_front(&head, novo2);

        printf("\nLista apoes adicionar novos elementos no inicio:\n");
        print_list(head);

        printf("Add_back\n");
        ft_lstadd_back(&head, novo3);
        print_list(head);
        return (0);
}*/
