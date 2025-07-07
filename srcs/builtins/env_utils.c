/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:59:51 by joaomart          #+#    #+#             */
/*   Updated: 2025/06/30 15:48:29 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_add(t_shell *shell, char *new_var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	j = 0;
	while (j < i)
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
	{
		free(new_env);
		return ;
	}
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}

char	*get_env_key(const char *str)
{
	int		len;
	char	*key;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, str, len + 1);
	return (key);
}

int	find_env_index(char **env, const char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (-1);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& (env[i][key_len] == '=' || env[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	add_or_update_env(t_shell *shell, char *arg)
{
	char	*key;
	int		index;

	key = get_env_key(arg);
	if (!key)
		return ;
	index = find_env_index(shell->env, key);
	if (index >= 0)
	{
		free(shell->env[index]);
		shell->env[index] = ft_strdup(arg);
	}
	else
		env_add(shell, arg);
	free(key);
}

bool	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || str[0] == '\0' || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}
