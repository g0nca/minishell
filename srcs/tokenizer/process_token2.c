/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:18:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/14 11:45:22 by ggomes-v         ###   ########.fr       */
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
    
    quote = line[*i];
    list->quotes_check = 1;
    *type_quotes = ternary_operator(list, quote);
    (*i)++; // Move past opening quote
    start = *i;
    while (line[*i] && line[*i] != quote) // Find closing quote
    {
        if (line[*i] == quote)
            list->quotes_check = 0;
        (*i)++;
    }
    word = ft_strndup(&line[start], *i - start); // Extract content inside quotes
    if (line[*i]) // Move past closing quote if found
        (*i)++;
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

// Function to add the final token to the list
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
