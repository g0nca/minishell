/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:26:14 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/08 15:13:20 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_list *tokenizer(char *line)
{
    t_token_list    *list;
    int             i;

    list = malloc(sizeof(t_token_list));
    if (!list)
        return (NULL);
    init_token_struct(list);
    i = 0;
    while (line[i])
    {
        if (ft_isspace(line[i]))
            i++;
        else if (line[i])
            process_token(list, line, &i);
    }
    check_command(list);
    //adicionar aqui a nova funcao para atribuir o valor de comando
    return (list);
}

void add_token(t_token_list *list, char *val, t_token_type type)
{
    if (!list || !val)
        return;

    t_token *new_token = create_token(val, type);
    if (!new_token)
        return;

    add_token_to_list(list, new_token);
}
t_token *create_token(char *val, t_token_type type)
{
    if (!val)
        return (NULL);

    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);

    new_token->value = ft_strdup(val);
    if (!new_token->value)
    {
        free(new_token);
        return (NULL);
    }

    new_token->type = type;
    new_token->next = NULL;
    new_token->prev = NULL;

    return (new_token);
}

void add_token_to_list(t_token_list *list, t_token *new_token)
{
    if (!list || !new_token)
        return;
    if (!list->tokens)
        list->tokens = new_token;
    else
    {
        t_token *last = list->tokens;
        while (last->next)
            last = last->next;
        if (last)
        {
            last->next = new_token;
            new_token->prev = last;
        }
        else
            list->tokens = new_token;
    }
    list->size++;
}
