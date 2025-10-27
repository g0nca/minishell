/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/27 15:29:00 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	check_if_expand(t_token *current)
{
	int	i;

	while (current)
	{
		if (current->value)
		{
			i = 0;
			while (current->value[i])
			{
				if (current->value[i] == '$')
					return (true);
				i++;
			}
		}
		if (current->next)
			current = current->next;
		else
			break ;
	}
	return (false);
}

/**
 * @brief Iterates through the token list and expands any environment variables.
 *
 * This function traverses each token in the linked list and calls a helper
 * function to handle environment variable expansion for each individual token.
 *
 * @param list Pointer to the first token in the list.
 * @param shell Pointer to the shell structure containing the
 *   environment variables.
 * @return Always returns 0.
 */
int	expander(t_token **tokens, t_shell *shell)
{
	t_token	*current;
	t_token	*next;
	int		skip_current;

	if (!tokens || !*tokens)
		return (0);
	current = *tokens;
	if (check_if_expand(current) == true)
	{
		current = *tokens;
		while (current)
		{
			next = current->next;
			skip_current = expander2(current, shell);
			if (skip_current || current->type == -1)
				remove_old_env_variable(tokens, current);
			current = next;
		}
	}
	return (0);
}

/**
 * @brief Expands environment variables in a given token if applicable.
 *
 * This function checks if the token type allows expansion (WORD, DOUBLE_QUOTE),
 * then scans for environment variable patterns (e.g., $VAR). If a valid variable
 * is found in the shell's environment, the token's value is replaced
 *   with its expanded form.
 *
 * Note: Expansion is skipped for tokens enclosed in single quotes.
 *
 * @param list Pointer to the token to be expanded.
 * @param shell Pointer to the shell structure containing
 *   the environment variables.
 * @return Always returns 0.
 */
int	expander2(t_token *list, t_shell *shell)
{
	int	skip_token;

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
int	expander3(t_token *list, t_shell *shell)
{
	char	*expanded;

	if (should_skip_expansion(list, shell) == 1)
		return (0);
	else
	{
		expanded = expand_variables(list->value, shell->env, list);
		free(list->value);
		if (expanded == (char *)-1)
		{
			list->value = NULL;
			return (1);
		}
		list->value = expanded;
	}
	return (0);
}

/**
 * @brief Expands environment variables found in a given input string.
 *
 * This function scans the input string for environment variable patterns
 * prefixed with '$' (e.g., $HOME, $PATH). When a variable is detected, it
 * retrieves its value from the environment (envp) and appends it to the result.
 *
 * Non-variable characters are copied directly to the result string.
 *
 * Percorre a string de input e copia caractere por caractere
 *   para a string de saída.
 * Quando encontra um '$' seguido de uma variável (ex: $USER),
 *   substitui pelo valor correspondente.
 * Utiliza um ponteiro auxiliar 'current' para escrever na memória alocada,
 *   enquanto 'result' permanece apontando para o início da string resultante.
 * No final, retorna 'result', que contém o input expandido
 *   com as variáveis de ambiente.
 * @param input The input string that may contain environment variables.
 * @param envp The array of environment variables in the form "VAR=value".
 * @param list Unused in this function (reserved for future use or context).
 * @return A newly allocated string with the expanded variables.
 *   Must be freed by the caller.
 */
char	*expand_variables(const char *input, char **envp, t_token *list)
{
	char	*result;
	char	*current;
	size_t	size;

	size = calculate_final_size(input, envp, list);
	if (size == 0)
		return ((char *)-1);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	current = result;
	while (*input)
	{
		if (*input == '\"' && list->in_single_quotes == 0)
			input_with_quotes(&input, &current, 2, list);
		else if (*input == '\'' && list->in_double_quotes == 0)
			input_with_quotes(&input, &current, 1, list);
		else if (*input == '$' && list->in_single_quotes == 0)
			copy_env_value(&input, &current, envp);
		else
			*current++ = *input++;
	}
	*current = '\0';
	return (result);
}
