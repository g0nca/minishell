/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:46:10 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/28 12:35:46 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_env_key_match(const char *env_var, const char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(env_var, key, key_len) != 0)
		return (0);
	if (env_var[key_len] == '\0' || env_var[key_len] == '=')
		return (1);
	return (0);
}

static int	count_env_entries(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

static char	**create_env_without_key(char **env, const char *key)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	count = count_env_entries(env);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!is_env_key_match(env[i], key))
			new_env[j++] = env[i];
		else
			free(env[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	remove_env_var(t_shell *shell, const char *key)
{
	char	**new_env;

	if (find_env_index(shell->env, key) == -1)
		return ;
	new_env = create_env_without_key(shell->env, key);
	if (!new_env)
		return ;
	free(shell->env);
	shell->env = new_env;
}

void	ft_unset(t_token *cmdargs, t_shell *shell)
{
	t_token	*current;

	current = cmdargs->next;
	while (current)
	{
		remove_env_var(shell, current->value);
		shell->last_exit_status = 0;
		current = current->next;
	}
}
