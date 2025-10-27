/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:19:51 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/27 13:38:42 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_command(t_token *list, t_shell *shell)
{
	t_token	*head;

	if (!list)
		return ;
	head = list;
	if (head->next)
		head = head->next;
	else
		return ;
	while (head)
	{
		if (head->value)
			commands(head, shell);
		if (head->next)
			head = head->next;
		else
			break ;
	}
}

void	commands(t_token *head, t_shell *shell)
{
	if (!head)
		return ;
	if (!ft_strcmp(head->value, "cd"))
		head->type = 1;
	else if (!ft_strcmp(head->value, "pwd"))
		head->type = 1;
	else if (!ft_strcmp(head->value, "echo"))
		head->type = 1;
	else if (!ft_strcmp(head->value, "env"))
		head->type = 1;
	else if (!ft_strcmp(head->value, "exit"))
		head->type = 1;
	else if (!ft_strcmp(head->value, "export"))
		head->type = 1;
	else if (!ft_strcmp(head->value, "unset"))
		head->type = 1;
	else if (!ft_strcmp(head->value, "test"))
		head->type = 0;
	else if (check_executable_cmd(head, shell) == 1)
		head->type = 1;
}

static char	*find_bin_path(char **splitted_path_env)
{
	int		i;
	char	*bin_path;

	i = 0;
	bin_path = NULL;
	while (splitted_path_env[i])
	{
		if (ft_strcmp(splitted_path_env[i], "/bin") == 0)
		{
			bin_path = ft_strjoin(splitted_path_env[i], "/");
			break ;
		}
		i++;
	}
	return (bin_path);
}

static int	check_access_to_executable(t_token *head, char *bin_path)
{
	char	*final_path;
	int		result;

	final_path = ft_strjoin(bin_path, head->value);
	free(bin_path);
	result = access(final_path, X_OK);
	if (result == 0)
		head->type = 1;
	free(final_path);
	return (result == 0);
}

int	check_executable_cmd(t_token *head, t_shell *shell)
{
	char	*path_env;
	char	**splitted_path_env;
	char	*bin_path;

	path_env = get_path_env(shell->env);
	if (path_env == NULL)
		return (0);
	splitted_path_env = ft_split(path_env, ':');
	bin_path = find_bin_path(splitted_path_env);
	free_env(splitted_path_env);
	if (!bin_path)
		return (0);
	return (check_access_to_executable(head, bin_path));
}
