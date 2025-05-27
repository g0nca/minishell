/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:30:17 by andrade           #+#    #+#             */
/*   Updated: 2025/05/27 21:40:35 by andrade          ###   ########.fr       */
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
		ft_printf_fd(2, "minishell: warning: ");
		ft_printf_fd(2, "shell level (1000) too high, resetting to 1\n");
		shlvl = 1;
	}
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return ;
	set_env_var(shell, "SHLVL", new_shlvl);
	free(new_shlvl);
}
