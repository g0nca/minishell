/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:08:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/24 12:02:59 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	run_builtin(t_token *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->value, "echo") == 0)
		ft_echo(cmd, shell);
	else if (ft_strcmp(cmd->value, "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(cmd->value,"cd") == 0)
		ft_cd(cmd, shell);
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
