/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:08:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/10 10:29:45 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	run_builtin(t_token_list *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->tokens->value, "echo") == 0)
		ft_echo(cmd, shell);
}

void	verify_token(t_token_list *type, t_shell *shell)
{
	if (type->tokens->type == 1)
	{
		run_builtin(type, shell);
	}
}
