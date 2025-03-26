/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:16:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/05 12:48:58 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
void	print_list(t_list *lst)
{
	t_list *temp = lst;
	while(temp)
	{
		printf("%s -> ", (char *)temp->content);
		temp = temp->next;
	}
	printf("NULL\n");
}

int	main(void)
{
	t_list	*head = ft_lstnew("Primeiro Elemento");

	t_list	*novo1 = ft_lstnew("Novo Elemento 1");
	t_list	*novo2 = ft_lstnew("Novo Elemento 2");

	printf("Lista Original\n");
	print_list(head);

	ft_lstadd_front(&head, novo1);
	ft_lstadd_front(&head, novo2);

	printf("\nLista apoes adicionar novos elementos no inicio:\n");
	print_list(head);

	return (0);
}
*/
