/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:27:29 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/19 11:27:29 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Retrieves the value of a specified environment variable.
 *
 * Searches the envp array for a variable matching the given name and
 * returns a pointer to the corresponding value (i.e., the part after '=').
 *
 * For example, if name = "PATH" and envp[i] = "PATH=/usr/bin",
 * the function returns a pointer to "/usr/bin".
 *
 * @param name The name of the environment variable to search for (e.g., "HOME").
 * @param envp Array of environment variables in the format "VAR=value".
 * @return A pointer to the value part of the environment 
 *   variable, or NULL if not found.
 */
char	*get_env_value(const char *name, char **envp)
{
	int	len;
	int	i;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * Check if token should be skipped due to quote type
 * 
 * @param list The token to check
 * @param shell The shell structure
 * @return 1 if token should be skipped, 0 otherwise
 */
int	should_skip_expansion(t_token *list, t_shell *shell)
{
	if (!list || !list->value)
		return (1);
	else if (verifiy_enviroment_var(shell, list->value) == 1)
		return (0);
	return (0);
}
