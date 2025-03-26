/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:35:40 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/05 15:55:02 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	del(void *content)
{
	free(content);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
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
	char *str = malloc(sizeof(char) * 4);
        t_list  *head = ft_lstnew(str);
	
	t_list *cur = head;

        t_list  *novo1 = ft_lstnew(str);
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

	printf("Deletar conteudo de um No:"); 
	ft_lstdelone(cur, del);
	print_list(head);
        return (0);
}*/
