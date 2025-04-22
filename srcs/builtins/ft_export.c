/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:18:11 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/22 10:45:12 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	env_count(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return (i);
}

static void	sort_env(char **env, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_line(char *env_var)
{
	char	*equal;
	int		var_len;

	equal = ft_strchr(env_var, '=');
	if (equal)
	{
		var_len = equal - env_var;
		printf("declare -x %.*s=\"%s\"\n", var_len, env_var, equal + 1);
	}
	else
		printf("declare -x %s\n", env_var);
}

void	print_export(t_shell *shell)
{
	char	**sorted_env;
	int		i;
	int		count;

	count = env_count(shell->env);
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return;
	i = 0;
	while (i < count)
	{
		if (shell->env[i] == NULL) {
			printf("Warning: NULL environment entry at index %d\n", i);
			break;
		}
		sorted_env[i] = ft_strdup(shell->env[i]);
		if (!sorted_env[i])
		{
			while (i > 0)
			{
				i--;
				free(sorted_env[i]);
			}
			free(sorted_env);
			return;
		}
		i++;
	}
	sorted_env[i] = NULL;
	sort_env(sorted_env, count);
	i = 0;
	while (sorted_env[i])
	{
		if (sorted_env[i][0] == '\0') {
			printf("Warning: Empty environment entry at index %d\n", i);
		} else {
			print_export_line(sorted_env[i]);
		}
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
	shell->last_exit_status = EXIT_SUCCESS;
}

void	ft_export(t_token *cmdargs, t_shell *shell)
{
	t_token	*current;

	current = cmdargs->next;
	if (!current)
		return (print_export(shell));
	while (current)
	{
		if (!is_valid_identifier(current->value))
		{
			shell_error(shell, current->value, 10, false);
			shell->last_exit_status = 1;
		}
		else if (ft_strchr(current->value, '='))
		{
			add_or_update_env(shell, current->value);
			shell->last_exit_status = 0;
		}
		else
		{
			if (find_env_index(shell->env, current->value) == -1)
				env_add(shell, current->value);
			shell->last_exit_status = 0;
		}
		current = current->next;
	}
}
