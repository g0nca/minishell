/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/24 14:02:29 by ggomes-v         ###   ########.fr       */
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
		 {
			 if (current->prev == NULL)
				 *tokens = current->next;
			 if (current->prev)
				 current->prev->next = current->next;
			 if (current->next)
				 current->next->prev = current->prev;
			 if (current->value)
				 free(current->value);
			 free(current);
		 }
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

int expander3(t_token *list, t_shell *shell)
{
	int i;
	int skip_token;
	char *expanded;

	skip_token = 0;
	expanded = NULL;
	i = 0;
	while (list->value[i])
	{
		if (list->value[i] == '$' && ft_isalpha(list->value[i + 1])
			&& list->type != TOKEN_SIMPLE_QUOTE
			&& verifiy_enviroment_var(shell, list->value) == 1)
		{
			expanded = expand_variables(list->value, shell->env, list);
			free(list->value);
			list->value = expanded;
		}
		else if (verifiy_enviroment_var(shell, list->value) == 1 && list->type == TOKEN_SIMPLE_QUOTE)
			break ;
		else if (list->value[i] == '$' && ft_isalpha(list->value[i + 1]))
		{
			invalid_env_var(list, shell);
			break ;
		}
		i++;
	}
	return (skip_token);
}

/**
 * Handles invalid environment variable expansion by nullifying the node data
 * instead of immediately deleting it to prevent access to freed memory.
 * 
 * @param list The token node containing the invalid environment variable
 * @param shell The shell structure
 * @return 1 to signal to expander2 that the token needs to be skipped
 */
int    invalid_env_var(t_token *list, t_shell *shell)
{
    if (!list)
        return (0);
    if (list->value)
    {
        free(list->value);
        list->value = NULL;
    }
    list->type = -1;
    shell->last_exit_status = 1;
    return (1);
}



/**
 * @brief Checks if a given token (environment variable name)
 * exists in the shell environment.
 *
 * This function iterates through the environment variables stored in the shell
 * and checks whether the provided token matches any of the variable names.
 *
 * @param shell Pointer to the shell structure containing the environment array.
 * @param token The token to be checked (e.g., "$PATH", "$HOME").
 * @return 1 if the environment variable is found, 0 otherwise.
 */
int	verifiy_enviroment_var(t_shell *shell, char *token)
{
	int j;
	
	j = 0;
	while (shell->env[j])
	{
		if (ft_strcmp_enviroment_variables(shell->env[j], token) == 0)
			return (1);
		j++;
	}
	return (0);
}
/**
 * @brief Compares an environment variable with a token representing a variable name.
 *
 * Skips any leading '$' characters in the token and compares the variable name part
 * (before the '=' character) of the environment variable with the token.
 *
 * @param env_var A string in the form "VAR=value".
 * @param token A token like "$VAR", possibly with multiple leading '$'.
 * @return 0 if the names match, 1 otherwise.
 */
int	ft_strcmp_enviroment_variables(char *env_var, char *token)
{
	int i;
	int j;
	int start;

	if (!env_var || !token)
		return (1);
	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			start = i;
			while (ft_isalnum(token[i]) || token[i] == '_')
				i++;
			j = 0;
			while (env_var[j] && env_var[j] != '=' && start < i)
			{
				if (env_var[j] != token[start])
					break;
				j++;
				start++;
			}
			if (env_var[j] == '=' && start == i)
				return (0);
		}
		else
			i++;
	}
	return (1);
}

