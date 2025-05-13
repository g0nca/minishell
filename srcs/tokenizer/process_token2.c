/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:18:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/16 12:55:48 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// Main tokenizer_word function
void tokenizer_word(t_token *list, int *i, char *line)
{
    char *word;
    char *joined;
    int type_quotes;

    type_quotes = 0;
    joined = NULL;
    if (!list || !i || !line)
        return;
    // Process all characters in current word
    while (line[*i] && !ft_isspace(line[*i]) &&
           line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
    {
        if (line[*i] == '\'' || line[*i] == '\"')
            word = handle_quoted_text(line, i, &type_quotes, list);
        else
            word = handle_regular_text(line, i);
        joined = join_word(joined, word);
        if (!joined)
            return ;
    }
    // Add the final token to the list
    add_final_token(list, joined, type_quotes);
}
// Function to handle quoted text in tokenizer
char *handle_quoted_text(char *line, int *i, int *type_quotes, t_token *list)
{
    char quote;
    char *word;
    int start;
    int end;
    
    quote = line[*i];
    *type_quotes = ternary_operator(list, quote);
    start = *i;           // Marca a posição da aspa inicial
    (*i)++;               // Avança para dentro das aspas

    while (line[*i] && line[*i] != quote)
        (*i)++;           // Avança até encontrar a aspa de fechamento

    if (line[*i] == quote)
        (*i)++;           // Inclui a aspa de fechamento no recorte final

    end = *i;

    // Caso haja outra aspa imediatamente a seguir (ex: 'abc'"def")
    word = ft_strndup(&line[start], end - start); // Inclui aspas
    return (word);
}


// Function to handle regular text in tokenizer
char *handle_regular_text(char *line, int *i)
{
    int start;

    start = *i;
    // Find end of word
    while (line[*i] && !ft_isspace(line[*i]) &&
           line[*i] != '|' && line[*i] != '<' &&
           line[*i] != '>' && line[*i] != '\'' && line[*i] != '"')
        (*i)++;
    // Extract the word
    return (ft_strndup(&line[start], *i - start));
}

// Function to join new word with existing text
char *join_word(char *joined, char *word)
{
    char *temp;

    if (!word)
        return (joined);
    if (!joined)
        return (word);
    temp = ft_strjoin(joined, word);
    free(joined);
    free(word);
    return temp;
}
