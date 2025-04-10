/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:19:51 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/10 13:20:38 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void check_command(t_token *list)
{
    t_token *head;
    
    if (!list)
        return;
    head = list;
    if (head->next) // Only advance if there's a next element
        head = head->next;
    else
        return ; // Return early if there's no next element
    while (head)
    {
        if (head->value) // Check that value exists before using it
            commands(head);
        if (head->next) // Move to next element if it exists
            head = head->next;
        else
            break;
    }
}

void	commands(t_token *head)
{
	if (!head)
		return ;
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
