/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:05:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/09/16 13:29:23 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_arg_count(t_token *cmdargs)
{
	t_token	*current;
	int		arg_count;

	arg_count = 0;
	current = cmdargs->next;
	while (current)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

bool	cd_oldpwd(t_shell *shell)
{
	char	*oldpwd_val;

	oldpwd_val = cd_getenv(shell, "OLDPWD");
	if (!oldpwd_val)
	{
		shell_error(shell, "OLDPWD not set", 0, false);
		return (false);
	}
	if (chdir(oldpwd_val) != 0)
	{
		shell_error(shell, oldpwd_val, 2, false);
		return (false);
	}
	printf("%s\n", oldpwd_val);
	shell->last_exit_status = EXIT_SUCCESS;
	return (true);
}

static bool	cd_process_path(t_token *current, t_shell *shell)
{
	if (!current || !ft_strcmp(current->value, "~")
		|| !ft_strcmp(current->value, "--"))
	{
		cd_home(shell);
		return (shell->last_exit_status == EXIT_SUCCESS);
	}
	else if (!ft_strcmp(current->value, "-"))
	{
		return (cd_oldpwd(shell));
		return (shell->last_exit_status == EXIT_SUCCESS);
	}
	else
	{
		cd_val(current->value, shell);
		return (shell->last_exit_status == EXIT_SUCCESS);
	}
}

static void	execute_cd(t_token *current, t_shell *shell, char *old_pwd)
{
	bool	cd_success;

	cd_success = cd_process_path(current, shell);
	if (cd_success)
		sucess_cd(old_pwd, shell);
	free(old_pwd);
}

void	ft_cd(t_token *cmdargs, t_shell *shell)
{
	t_token	*current;
	char	*old_pwd;
	char	*pwd_from_env;

	current = cmdargs->next;
	if (ft_arg_count(cmdargs) > 1)
	{
		g_exit_status = 1;
		shell->last_exit_status = 1;
		shell_error(shell, "", 9, EXIT_SUCCESS);
		return ;
	}
	pwd_from_env = cd_getenv(shell, "PWD");
	if (pwd_from_env)
		old_pwd = ft_strdup(pwd_from_env);
	else
		old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		shell_error(shell, "getcwd error", 0, false);
		return ;
	}
	execute_cd(current, shell, old_pwd);
}
