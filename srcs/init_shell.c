/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:22:45 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/27 14:15:17 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	int		count;
	char	**env_copy;

	count = 0;
	i = 0;
	while (envp[count])
		count++;
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return (NULL);
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

t_shell	*init_shell(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)av;
	(void)ac;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = copy_env(envp);
	shell->last_exit_status = 0;
	shell->running = 1;
	shell->heredoc_files = 0;
	shell->temp_heredoc_path = NULL;
	shell->in = NULL;
	shell->out = NULL;
	shell->append = NULL;
	shell->heredoc = NULL;
	shell->token = NULL;
	shell->tree = NULL;
	shell->heredoc_counter = 0;
	return (shell);
}
