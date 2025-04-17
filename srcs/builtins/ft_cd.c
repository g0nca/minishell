/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:05:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/17 10:46:45 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_home(t_shell *shell)
{
	char	*target;
	target = cd_getenv(shell, "HOME");
	if (!target)
		return (shell_error(shell, "HOME not set", 0, false));
	if (chdir(target) != 0)
		return (shell_error(shell, (char *)target, 2, false));
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

// Helper function to get environment variable from shell's environment
char *cd_getenv(t_shell *shell, const char *name)
{
	int		i;
	size_t	name_len;
	
	name_len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], name, name_len) && 
			shell->env[i][name_len] == '=')
		{
			return (shell->env[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
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
	char    *oldpwd_val;
	
	current = cmdargs->next;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (shell_error(shell, "getcwd error", 0, false));
	
	if (!current || !ft_strcmp(current->value, "~") || !ft_strcmp(current->value, "--"))
	{
		cd_home(shell);
	}
	else if (!ft_strcmp(current->value, "-"))
	{
		// Special handling for cd -
		oldpwd_val = cd_getenv(shell, "OLDPWD");
		if (!oldpwd_val)
		{
			shell_error(shell, "OLDPWD not set", 0, false);
			free(old_pwd);
			return;
		}
		
		if (chdir(oldpwd_val) != 0)
		{
			shell_error(shell, oldpwd_val, 2, false);
			free(old_pwd);
			return;
		}
		
		printf("%s\n", oldpwd_val);
		
		// Get new current directory after changing
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			// Update the environment variables
			update_env_var(shell, "OLDPWD", old_pwd);
			update_env_var(shell, "PWD", new_pwd);
			free(new_pwd);
		}
		
		free(old_pwd);
		shell->last_exit_status = EXIT_SUCCESS;
		return;
	}
	else
	{
		target = current->value;
		cd_val(target, shell);
	}
	
	// Handle environment variable updates for other cd cases
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(old_pwd);
		return (shell_error(shell, "getcwd error", 0, false));
	}
	
	update_env_var(shell, "OLDPWD", old_pwd);
	update_env_var(shell, "PWD", new_pwd);
	
	// For debugging - uncomment if needed
	// printf("DEBUG - After cd: PWD=%s, OLDPWD=%s\n", 
	//        cd_getenv(shell, "PWD"), cd_getenv(shell, "OLDPWD"));
	
	free(old_pwd);
	free(new_pwd);
	shell->last_exit_status = EXIT_SUCCESS;
}