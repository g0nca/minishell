/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:19:51 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/09 15:23:03 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    check_command(t_token_list *list)
{
    t_token *head;

    if (!list->tokens)
        return ;
    head = list->tokens;
    while (head->value)
    {
		commands(list);
        if (head->next != NULL)
            head = head->next;
        else
            break ;
    }
}

void	commands(t_token_list *list)
{
	if (!ft_strcmp(head->value, "cd") && head->type == 0)
		head->type = 1;
	else if(!ft_strcmp(head->value, "pwd") && head->type == 0)
		head->type = 1;
	else if(!ft_strcmp(head->value, "echo") && head->type == 0)
		head->type = 1;
	else if(!ft_strcmp(head->value, "env") && head->type == 0)
		head->type = 1;
	else if(!ft_strcmp(head->value, "exit") && head->type == 0)
		head->type = 1;
	else if(!ft_strcmp(head->value, "export") && head->type == 0)
		head->type = 1;
	else if(!ft_strcmp(head->value, "unset") && head->type == 0)
		head->type = 1;
}