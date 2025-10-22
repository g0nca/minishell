/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:55 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/22 11:08:30 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Compare a portion of token with environment variable name
 *
 * @param env_var The environment variable string to compare
 * @param token The token string containing potential variable reference
 * @param start Starting index of variable name in token
 * @param end Ending index of variable name in token
 * @return 0 if matches, 1 otherwise
 */
int	compare_env_name(char *env_var, char *token, int start, int end)
{
	int	j;

	j = 0;
	while (env_var[j] && env_var[j] != '=' && start < end)
	{
		if (env_var[j] != token[start])
			return (1);
		j++;
		start++;
	}
	if (env_var[j] == '=' && start == end)
		return (0);
	return (1);
}

/**
 * Check if a token contains an environment variable that matches env_var
 *
 * @param env_var The environment variable string to check
 * @param token The token string to check for variable references
 * @return 0 if match found, 1 otherwise
 */
int	ft_strcmp_enviroment_variables(char *env_var, char *token)
{
	int	i;
	int	start;

	if (!env_var || !token)
		return (1);
	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			start = i;
			while ((ft_isalnum(token[i]) || token[i] == '_'))
				i++;
			if (compare_env_name(env_var, token, start, i) == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
}

/**
 * Handles invalid environment variable expansion by nullifying the node data
 * instead of immediately deleting it to prevent access to freed memory.
 *
 * @param list The token node containing the invalid environment variable
 * @param shell The shell structure
 * @return 1 to signal to expander2 that the token needs to be skipped

int	invalid_env_var(t_token *list, t_shell *shell)
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
}*/

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
	int	j;

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
 * remove_invalid_env_variable - Removes an invalid environment
 *   variable token from the token list.
 *
 * This function removes a node from a doubly linked
 *   list of tokens that represents an invalid or
 *   undefined environment variable.
 * It properly updates the pointers of neighboring nodes to
 *   maintain the list integrity, and frees all memory associated
 *   with the removed token.
 *
 * @tokens: Pointer to the head pointer of the token list.
 * @current: Pointer to the token node to be removed.
 *
 * Return: 0 on success.
 */
int	remove_old_env_variable(t_token **tokens, t_token *current)
{
	if (current->prev == NULL)
		*tokens = current->next;
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	if (current->value)
	{
		free(current->value);
		current->value = NULL;
	}
	free(current);
	current = NULL;
	return (0);
}
