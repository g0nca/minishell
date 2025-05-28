/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:08:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/28 10:38:09 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	run_builtin(t_token *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->value, "echo") == 0)
		ft_echo(cmd, shell);
	else if (ft_strcmp(cmd->value, "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(cmd->value, "cd") == 0)
		ft_cd(cmd, shell);
	else if (ft_strcmp(cmd->value, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(cmd->value, "export") == 0)
		ft_export(cmd, shell);
	else if (ft_strcmp(cmd->value, "unset") == 0)
		ft_unset(cmd, shell);
	else if (ft_strcmp(cmd->value, "exit") == 0)
		ft_exit(shell, cmd);
}

void	verify_token(t_token *type, t_shell *shell)
{
	if (!type || !shell)
		return ;
	if (type->type == 1)
	{
		run_builtin(type, shell);
	}
}
