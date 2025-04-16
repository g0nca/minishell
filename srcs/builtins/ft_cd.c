/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:05:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/16 17:40:06 by joaomart         ###   ########.fr       */
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

void	ft_cd(t_token *cmdargs, t_shell *shell)
{
	t_token	*current;
	char	*old_pwd;
	char	*new_pwd;
	char	*target;

	current = cmdargs->next; // cmdargs é o "cd", o argumento está no seguinte
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
	new_pwd = getcwd(NULL, 0);
	if (old_pwd)
		setenv("OLDPWD", old_pwd, 1);
	if (new_pwd)
		setenv("PWD", new_pwd, 1);
	free(old_pwd);
	free(new_pwd);
	shell->last_exit_status = EXIT_SUCCESS;
}
