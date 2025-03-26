/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:02:44 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/06 10:24:13 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;

	while (*lst)
	{
		next_node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_node;
	}
	*lst = NULL;
}
/*
//next_node = (*lst)->next;
//como **lst e um ponteiro para um ponteiro para o primeiro no da lista
// *lst e um ponteiro para o no atual, entao (*lst)->next e o proximo no da lista
// como lst e um ponteiro duplo (t_list **lst) ao usar 
// *lst estamos acessar o ponteiro
// para o no atual colocamos entre parenteses para deixar claro que ->next esta 
// acessando o proximo no do ponteiro e nao o proximo no de lst diretamente
//se escrevessemos *lst->next o compilador interpretaria 
//como *(lst->next), oque resultaria em erro, 
//pois lst e um ponteiro e nao possui o campo next. 
//Por isso os parenteses sao necessarios para indicar que queremos 
//acessar o campo next do no para o qual *lst aponta
void    print_list(t_list *lst)
{
       // t_list *temp = lst;
        while(lst)
        {
                printf("%s -> ", (char *)lst->content);
                lst = lst->next;
        }
        printf("NULL\n");
}


int	main(void)
{
	t_list	*head = ft_lstnew(ft_strdup("1 Elemento"));
	t_list	*novo1 = ft_lstnew(ft_strdup("2 Elemento"));
	t_list	*novo2 = ft_lstnew(ft_strdup("3 Elemento"));

	head->next = novo1;
	novo1->next = novo2;
	
	print_list(head);
	printf("Limpar a Lista...\n");
	ft_lstclear(&head, free);
	
	print_list(head);
	if (!head)
		printf("Lista limpa com sucesso !");
	else
		printf("Erro ao limpar a lista");
	return (0);
}*/
