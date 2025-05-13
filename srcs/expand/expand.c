/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/06 14:57:41 by ggomes-v         ###   ########.fr       */
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
			remove_old_env_variable(tokens, current);
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
    char *expanded;

    if (should_skip_expansion(list, shell) == 1)
        return (0);
    else
    {
        expanded = expand_variables(list->value, shell->env, list);
        free(list->value);
        list->value = expanded;
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
    else if (verifiy_enviroment_var(shell, list->value) == 1)
		return (0); 
    return (0);
}

/**
 * Calculate the length needed for the expanded string
 * 
 * @param str The original string with special variables
 * @param list The token containing shell reference
 * @return The length needed for the expanded string
 */
int calculate_expanded_length(char *str, t_token *list)
{
    int i;
    int len;
    char *temp;
    
    len = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '$')
        {
            temp = ft_itoa(getpid());
            len += ft_strlen(temp);
            free(temp);
            i += 2;
        }
        else if (str[i] == '$' && str[i + 1] == '?')
        {
            temp = ft_itoa(list->shell_ref.last_exit_status);
            len += ft_strlen(temp);
            free(temp);
            i += 2;
        }
        else
        {
            len++;
            i++;
        }
    }
    return (len);
}

/**
 * Copy a special variable value into the destination string
 * 
 * @param dest The destination string
 * @param value The value to copy
 * @param pos Current position in destination string (updated)
 */
void copy_special_var(char *dest, char *value, int *pos)
{
    int i;
    
    i = 0;
    while (value[i])
    {
        dest[*pos] = value[i];
        (*pos)++;
        i++;
    }
}

/**
 * Expands special variable cases like $$ (process ID) and $? (exit status)
 * 
 * @param str The string containing the special variable
 * @param list The token being processed
 * @return The expanded string with special variables replaced
 */
char *expand_variable_special_cases(char *str, t_token *list)
{
    char *expanded;
    char *temp;
    int i;
    int j;
    
    if (!str)
        return (NULL);
    
    expanded = (char *)malloc(sizeof(char) * (calculate_expanded_length(str, list) + 1));
    if (!expanded)
        return (NULL);
    
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '$')
        {
            temp = ft_itoa(getpid());
            copy_special_var(expanded, temp, &j);
            free(temp);
            i += 2;
        }
        else if (str[i] == '$' && str[i + 1] == '?')
        {
            temp = ft_itoa(list->shell_ref.last_exit_status);
            copy_special_var(expanded, temp, &j);
            free(temp);
            i += 2;
        }
        else
            expanded[j++] = str[i++];
    }
    expanded[j] = '\0';
    
    return (expanded);
}

