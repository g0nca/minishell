/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:18 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/16 14:33:50 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}
// flag == 1 -> Filho
// flag == 0 -> Pai
void	free_struct(t_shell *shell, int flag)
{
	if (!shell)
		return ;
	if (flag == 0)
		cleanup_heredoc_files(shell);
	free_env(shell->env);
}

void	free_tokens(t_token **list)
{
	t_token	*next;
	
	if (!list || !*list)
		return ;
	while (*list)
	{
		next = (*list)->next;
		if ((*list)->value)
		{
			free((*list)->value);
			(*list)->value = NULL;
		}
		free((*list));
		(*list) = next;
	}
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	ft_free(char **str)
{
	if (!str || !*str)
		return ;
	free (*str);
	*str = NULL;
}

void	free_array_ref(char ***cmd)
{
	int	i;

	i = 0;
	if (!cmd || !(*cmd))
		return ;
	while ((*cmd)[i])
	{
		ft_free(&(*cmd)[i]);
		(*cmd)[i] = NULL;
		i++;
	}
	free (*cmd);
	*cmd = NULL;
}
