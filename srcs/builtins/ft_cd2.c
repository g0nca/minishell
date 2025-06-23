/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:48:30 by joaomart          #+#    #+#             */
/*   Updated: 2025/06/23 14:37:40 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_val(char *target, t_shell *shell)
{
	struct stat	path_stat;

	if (access(target, F_OK) != 0)
		return (shell_error(shell, target, 15, false));
	if (stat(target, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode))
		return (shell_error(shell, target, 6, false));
	if (access(target, X_OK) != 0)
		return (shell_error(shell, target, 3, false));
	if (chdir(target) != 0)
		return (shell_error(shell, target, 2, false));
	shell->last_exit_status = EXIT_SUCCESS;
}

char	*cd_getenv(t_shell *shell, const char *name)
{
	int		i;
	size_t	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], name, name_len)
			&& shell->env[i][name_len] == '=')
		{
			return (shell->env[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

static char	*create_env_entry(const char *name, const char *value)
{
	size_t	name_len;
	size_t	total_len;
	char	*new_entry;

	name_len = ft_strlen(name);
	total_len = name_len + 1 + ft_strlen(value) + 1;
	new_entry = malloc(total_len);
	if (!new_entry)
		return (NULL);
	ft_strlcpy(new_entry, name, total_len);
	ft_strlcat(new_entry, "=", total_len);
	ft_strlcat(new_entry, value, total_len);
	return (new_entry);
}

int	update_env_var(t_shell *shell, const char *name, const char *value)
{
	int		i;
	size_t	name_len;
	char	*new_entry;

	i = 0;
	name_len = ft_strlen(name);
	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (0);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], name, name_len)
			&& shell->env[i][name_len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (add_env_var(shell, new_entry, i));
}

int	add_env_var(t_shell *shell, char *new_entry, int env_size)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (env_size + 2));
	if (!new_env)
	{
		free(new_entry);
		return (0);
	}
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (1);
}
