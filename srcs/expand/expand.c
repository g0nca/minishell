/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/23 14:50:16 by ggomes-v         ###   ########.fr       */
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

int	expander(t_token *list, t_shell *shell)
{
	while (list)
	{
		expander2(list, shell);
		list = list->next;
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
	char *expanded;
	int i;

	expanded = NULL;
	if (list->type == TOKEN_WORD
		|| list->type == TOKEN_SIMPLE_QUOTE
		|| list->type == TOKEN_DOUBLE_QUOTE)
	{
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
			i++;
		}
	}
	return (0);
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
	
	i = 0;
	j = 0;

	if (!env_var || !token)
		return (1);
	while (token[j] == '$')
		j++;
	while (env_var[i] && env_var[i] != '=' && token[j])
	{
		if (env_var[i] != token[j])
			return (1);
		i++;
		j++;
	}
	if (env_var[i] == '=' && (token[j] == '\0' || token[j] == ' ')) 
		return (0);
	return (1);
}

