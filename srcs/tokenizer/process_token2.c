/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:18:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/10 09:36:44 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Function to handle quoted text in tokenizer
char *handle_quoted_text(char *line, int *i, int *type_quotes)
{
    char quote;
    char *word;
    int start;
    
    quote = line[*i];
    // Set quote type
    *type_quotes = (quote == '\'') ? 1 : 2;
    (*i)++;  // Move past opening quote
    start = *i;
    // Find closing quote
    while (line[*i] && line[*i] != quote)
        (*i)++;
    // Extract content inside quotes
    word = ft_strndup(&line[start], *i - start);
    // Move past closing quote if found
    if (line[*i])
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

// Main tokenizer_word function
void tokenizer_word(t_token_list *list, int *i, char *line)
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
            word = handle_quoted_text(line, i, &type_quotes);
        else
            word = handle_regular_text(line, i);
        joined = join_word(joined, word);
        if (!joined)
            return ;
    }
    // Add the final token to the list
    add_final_token(list, joined, type_quotes);
}

// Function to add the final token to the list
void add_final_token(t_token_list *list, char *joined, int type_quotes)
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
