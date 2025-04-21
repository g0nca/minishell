/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:18:11 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/21 12:23:18 by joaomart         ###   ########.fr       */
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
	int		i, j;
	char	*tmp;

	for (i = 0; i < count - 1; i++)
	{
		for (j = i + 1; j < count; j++)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
		}
	}
}

bool	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
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
		return ;
	i = 0;
	while (i < count)
	{
		sorted_env[i] = shell->env[i];
		i++;
	}
	sorted_env[i] = NULL;
	sort_env(sorted_env, count);
	i = 0;
	while (sorted_env[i])
		print_export_line(sorted_env[i++]);
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
			ft_error(10, current->value); // invalid identifier
			shell->last_exit_status = 1;
		}
		else
		{
			// add_or_update_env(shell, current->value); // your own function to insert/update env
			shell->last_exit_status = 0;
		}
		current = current->next;
	}
}
