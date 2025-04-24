/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:07:36 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/24 13:54:32 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

char	**token_to_args(t_token *token)
{
	int		count;
	int		i;
	t_token	*temp;

	count = 0;
	i = 0;
	temp = token;
	while (temp)
	{
		if (temp->type == TOKEN_CMD || temp->type == TOKEN_WORD)
			count++;
		temp = temp->next;
	}
	char **args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	temp = token;
	while (temp)
	{
		if (temp->type == TOKEN_CMD || temp->type == TOKEN_WORD)
			args[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

void	execute_command(t_token *token, t_shell *shell)
{
	if (token && token->type == TOKEN_CMD && is_builtin(token->value))
		return;
	else
		execute_external_command(token, shell);
}
