/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:05:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/16 18:40:38 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_home(t_shell *shell)
{
	char	*target;

	target = getenv("HOME");
	if (!target)
		return (shell_error(shell, "HOME not set", 0, false));
	if (chdir(target) != 0)
		return (shell_error(shell, (char *)target, 2, false));
}

void	cd_oldpwd(t_shell *shell)
{
	char	*target;

	target = getenv("OLDPWD");
	if (!target)
		return (shell_error(shell, "OLDPWD not set", 0, false));
	if (chdir(target) != 0)
		return (shell_error(shell, (char *)target, 2, false));
	printf("%s\n", target); // imprime o diretório novo
}

void	cd_val(char *target, t_shell *shell)
{
	struct stat	path_stat;

	if (access(target, F_OK) != 0)
		return (shell_error(shell, target, 2, false)); // No such file
	if (stat(target, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode))
		return (shell_error(shell, target, 6, false)); // Not a directory
	if (access(target, X_OK) != 0)
		return (shell_error(shell, target, 3, false)); // Permission denied
	if (chdir(target) != 0)
		return (shell_error(shell, target, 2, false)); // Outro erro genérico
}

int	update_env_var(t_shell *shell, const char *name, const char *value)
{
	int		i;
	char	*new_entry;
	size_t	name_len;
	size_t	total_len;
	char	**new_env;

	name_len = ft_strlen(name);
	total_len = name_len + 1 + ft_strlen(value) + 1;
	new_entry = malloc(total_len);
	if (!new_entry)
		return (0);
	ft_strlcpy(new_entry, name, total_len);
	ft_strlcat(new_entry, "=", total_len);
	ft_strlcat(new_entry, value, total_len);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], name, name_len) && shell->env[i][name_len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = new_entry;
			return (1);
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_entry);
		return (0);
	}
	i = 0;
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

void	ft_cd(t_token *cmdargs, t_shell *shell)
{
	t_token	*current;
	char	*old_pwd;
	char	*new_pwd;
	char	*target;

	current = cmdargs->next;
	old_pwd = getcwd(NULL, 0);
	if (!current || !ft_strcmp(current->value, "~")
		|| !ft_strcmp(current->value, "--"))
		cd_home(shell);
	else if (!ft_strcmp(current->value, "-"))
		cd_oldpwd(shell);
	else
	{
		target = current->value;
		cd_val(target, shell);
	}
	if (old_pwd)
		update_env_var(shell, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		update_env_var(shell, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	shell->last_exit_status = EXIT_SUCCESS;
}
