/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:30:17 by andrade           #+#    #+#             */
/*   Updated: 2025/05/27 15:54:07 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_var(t_shell *shell, const char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static void	set_env_var(t_shell *shell, const char *name, const char *value)
{
	int		i;
	size_t	len;
	char	*new_entry;
	char	*env_name;

	if (!name || !value)
		return;
	env_name = ft_strjoin(name, "=");
	new_entry = ft_strjoin(env_name, value);
	if (!new_entry)
		return;
	free(env_name);
	len = ft_strlen(name);
	i = 0;
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0 && shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = new_entry;
			return;
		}
		i++;
	}
	char **new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_entry);
		return;
	}
	i = 0;
	while (shell->env && shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(new_entry);
	free(shell->env);
	shell->env = new_env;
}

void	init_shlvl(t_shell *shell)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env_var(shell, "SHLVL");
	if (!shlvl_str)
		shlvl = 1;
	else
		shlvl = ft_atoi(shlvl_str) + 1;
	if (shlvl > 999)
	{
		ft_printf_fd(2, "./minishell: warning: shell level (1000) too high, resetting to 1\n");
		shlvl = 1;
	}
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return;
	set_env_var(shell, "SHLVL", new_shlvl);
	free(new_shlvl);
}
