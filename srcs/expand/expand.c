/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/30 12:23:02 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @brief Iterates through the token list and expands any environment variables.
 *
 * This function traverses each token in the linked list and calls a helper
 * function to handle environment variable expansion for each individual token.
 *
 * @param list Pointer to the first token in the list.
 * @param shell Pointer to the shell structure containing the environment variables.
 * @return Always returns 0.
 */

int expander(t_token **tokens, t_shell *shell)
{
	t_token *current;
	t_token *next;
	int skip_current;
	
	if (!tokens || !*tokens)
		return (0);
	current = *tokens;
	while (current)
	{
		next = current->next;
		skip_current = expander2(current, shell);
		if (skip_current || current->type == -1)
			remove_invalid_env_variable(tokens, current);
		current = next;
	}
	return (0);
}

/**
 * @brief Expands environment variables in a given token if applicable.
 *
 * This function checks if the token type allows expansion (WORD, DOUBLE_QUOTE),
 * then scans for environment variable patterns (e.g., $VAR). If a valid variable
 * is found in the shell's environment, the token's value is replaced with its expanded form.
 *
 * Note: Expansion is skipped for tokens enclosed in single quotes.
 *
 * @param list Pointer to the token to be expanded.
 * @param shell Pointer to the shell structure containing the environment variables.
 * @return Always returns 0.
 */

int	expander2(t_token *list, t_shell *shell)
{
	int skip_token;

	skip_token = 0;
	if (list->type == TOKEN_WORD
		|| list->type == TOKEN_SIMPLE_QUOTE
		|| list->type == TOKEN_DOUBLE_QUOTE)
	{
		skip_token = expander3(list, shell);
	}
	return (skip_token);
}

/**
 * Main expander function that processes a token for environment variables
 * 
 * @param list The token to process
 * @param shell The shell structure
 * @return 0 for normal execution, 1 if token should be skipped
 */
int expander3(t_token *list, t_shell *shell)
{
    int i;
    
    if (should_skip_expansion(list, shell) == 1)
        return (0);
    i = 0;
    while (list->value[i])
    {
        if (list->value[i] == '$' && 
            process_dollar_sign(list, shell, i))
            return (1);
        i++;
    }
    
    return (0);
}
/**
 * Check if token should be skipped due to quote type
 * 
 * @param list The token to check
 * @param shell The shell structure
 * @return 1 if token should be skipped, 0 otherwise
 */
int should_skip_expansion(t_token *list, t_shell *shell)
{
    if (!list || !list->value)
        return (1);
	else if (list->type == TOKEN_SIMPLE_QUOTE)
        return (1);
    else if (verifiy_enviroment_var(shell, list->value) == 1)
		return (0); 
    return (0);
}

/**
 * Process dollar sign in token value
 * 
 * @param list The token containing the value
 * @param shell The shell structure
 * @param i Current position in value string
 * @return 1 if token marked invalid, 0 otherwise
 */
int process_dollar_sign(t_token *list, t_shell *shell, int i)
{
    char *expanded;

    if (!ft_isalpha(list->value[i + 1]))
        return (0);
    if (verifiy_enviroment_var(shell, list->value) == 1 &&
        list->type != TOKEN_SIMPLE_QUOTE)
    {
        expanded = expand_variables(list->value, shell->env, list);
        free(list->value);
        list->value = expanded;
        return (0);
    }
    else
    {
        invalid_env_var(list, shell);
        return (1);
    }
}

