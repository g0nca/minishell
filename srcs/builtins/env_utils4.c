/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:36:16 by andrade           #+#    #+#             */
/*   Updated: 2025/05/27 21:42:23 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*create_env_entry(const char *name, const char *value)
{
	char	*env_name;
	char	*new_entry;

	if (!name || !value)
		return (NULL);
	env_name = ft_strjoin(name, "=");
	if (!env_name)
		return (NULL);
	new_entry = ft_strjoin(env_name, value);
	free(env_name);
	return (new_entry);
}

static int	update_exist_env(t_shell *shell, const char *name, char *new_entry)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	util_env_var(t_shell *shell, char *new_entry)
{
	int		i;
	char	**new_env;

	i = 0;
	while (shell->env && shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_entry);
		return ;
	}
	i = 0;
	while (shell->env && shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void	set_env_var(t_shell *shell, const char *name, const char *value)
{
	char	*new_entry;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return ;
	if (!update_exist_env(shell, name, new_entry))
		util_env_var(shell, new_entry);
}
