/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:18:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/08 15:13:05 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*t_token_list    *tokenizer_word(t_token_list *list, int *i, char *line)
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
}*/
void tokenizer_word(t_token_list *list, int *i, char *line)
{
    int     start;
    char    *word;
    char    quote;
    char    *joined = NULL;
    char    *temp;
    int     quotes;

    while (line[*i] && !ft_isspace(line[*i])  &&
          line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
    {
        quotes = 0;
        // Se encontra aspas
        if (line[*i] == '\'' || line[*i] == '\"')
        {
            if (line[*i] == '\'')
                quotes = 1;
            else if (line[*i] == '\"')
                quotes = 2;
            quote = line[*i];
            (*i)++;
            start = *i;
            while (line[*i] && line[*i] != quote)
                (*i)++;
            word = ft_strndup(&line[start], *i - start); // conteúdo dentro das aspas
            (*i)++; // avançar após a aspa de fecho

            if (!joined)
                joined = word;
            else
            {
                temp = ft_strjoin(joined, word);
                free(joined);
                free(word);
                joined = temp;
            }
        }
        else
        {
            start = *i;
            while (line[*i] && !ft_isspace(line[*i]) &&
                   line[*i] != '|' && line[*i] != '<' &&
                   line[*i] != '>' && line[*i] != '\'' && line[*i] != '"')
                (*i)++;

            word = ft_strndup(&line[start], *i - start);
            if (!joined)
                joined = word;
            else
            {
                temp = ft_strjoin(joined, word);
                free(joined);
                free(word);
                joined = temp;
            }
        }
    }
    if (joined)
    {
        if (quotes == 2)
            add_token(list, joined, TOKEN_DOUBLE_QUOTE);
        else if (quotes == 1)
            add_token(list, joined, TOKEN_SIMPLE_QUOTE);
        else
            add_token(list, joined, TOKEN_WORD);
        free(joined);
    }
}

void    check_command(t_token_list *list)
{
    t_token *head;

    head = list->tokens;
    while (head->value)
    {
        if (!ft_strcmp(head->value, "cd") && head->type == 0)
            head->type = 1;
        else if(!ft_strcmp(head->value, "pwd") && head->type == 0)
            head->type = 1;
        if (head->next != NULL)
            head = head->next;
        else
            break ;
    }
}
