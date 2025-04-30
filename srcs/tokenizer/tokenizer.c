/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:26:14 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/30 16:04:18 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token *tokenizer(char *line, t_shell *shell)
{
    t_token    *list;
    int             i;

    if (!line || !*line)
        return (NULL);
    list = malloc(sizeof(t_token));
    if (!list)
        return (NULL);
    init_token_struct(list);
    i = 0;
    while (line[i])
    {
        if (line[i] == '\0' && list->type != 0)
            break ;
        else if (ft_isspace(line[i]))
            i++;
        else if (line[i])
            process_token(list, line, &i);
    }
    check_command(list, shell);
    return (list);
}

void add_token(t_token *list, char *val, t_token_type type)
{
    t_token *new_token;

    if (!list || !val)
        return;
    new_token = create_token(val, type);
    if (!new_token)
        return;
    add_token_to_list(list, new_token);
}

t_token *create_token(char *val, t_token_type type)
{
    t_token *new_token;

    if (!val)
        return (NULL);
    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->value = ft_strdup(val);
    if (!new_token->value)
    {
        free(new_token);
        return (NULL);
    }
    //new_token->quotes_check = 0;
    new_token->type_quotes = 0;
    new_token->type = type;
    new_token->next = NULL;
    new_token->prev = NULL;
    new_token->heredoc_fd = -1;
    return (new_token);
}

void add_token_to_list(t_token *list, t_token *new_token)
{
    t_token *last;

    if (!list || !new_token)
        return;
    if (!list)
        list = new_token;
    else
    {
        last = list;
        while (last->next)
            last = last->next;
        if (last)
        {
            last->next = new_token;
            new_token->prev = last;
        }
        else
            list = new_token;
    }
    list->size++;
}
// Function to add the final token to the list with the correct quote
void add_final_token(t_token *list, char *joined, int type_quotes)
{
    if (!joined)
        return;
    if (type_quotes == 2)
        add_token(list, joined, TOKEN_DOUBLE_QUOTE);
    else if (type_quotes == 1)
        add_token(list, joined, TOKEN_SIMPLE_QUOTE);
    else
        add_token(list, joined, TOKEN_WORD);
    free(joined);
}
