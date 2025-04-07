/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:26:14 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/07 14:29:48 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void add_token(t_token_list *list, char *val, t_token_type type)
{
    int i;
    int new_capacity;
    t_token *new_tokens;

    i = 0;
    if (list->size >= list->capacity)
    {
        new_capacity = (list->capacity == 0) ? 8 : list->capacity * 2;
        new_tokens = malloc(sizeof(t_token) * new_capacity);
        if (!new_tokens)
            return;
        while (i < list->size)//copiar os tokens antigos
        {
            new_tokens[i].value = list->tokens[i].value;
            new_tokens[i].type = list->tokens[i].type;
            i++;
        }
        free(list->tokens);//libertar array antigo
        list->tokens = new_tokens;
        list->capacity = new_capacity;
    }
    list->tokens[list->size].value = ft_strdup(val);
    list->tokens[list->size].type = type;
    list->size++;
}


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
        if (line[i] == '|')
        {
            add_token(list, "|", TOKEN_PIPE);
            i++;
        }
        else if (line[i] == '>' && line[i+1] == '>')
        {
            add_token(list, ">>", TOKEN_APPEND);
            i += 2;
        }
        else if (line[i] == '<' && line[i+1] == '<')
        {
            add_token(list, "<<", TOKEN_HERE_DOC);
            i += 2;
        }
        else if (line[i] == '>')
        {
            add_token(list, ">", TOKEN_REDIR_OUT);
            i++;
        }
        else if (line[i] == '<')
        {
            add_token(list, "<", TOKEN_REDIR_IN);
            i++;
        }
        else
            tokenizer_word(list, &i, line);
    }
    return (list);
}
t_token_list    *tokenizer_word(t_token_list *list, int *i, char *line)
{
    int start;
    char *word;

    start = *i;
    while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
    {
        (*i)++;
    }
    word = ft_strndup(&line[start], *i - start);
    add_token(list, word, TOKEN_WORD);
    free(word); // Free the temporary string after it's been copied
    return (list);
}

void print_tokens(t_token_list *list)
{
    int i = 0;
    
    while (i < list->size)
    {
        printf("token[%d] (%d): %s\n", i, list->tokens[i].type, list->tokens[i].value);
        i++;
    }
}