/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:36:51 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/28 12:36:41 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_export_line(char *env_var)
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

	sorted_env = copy_and_sort_env(shell, &count);
	if (!sorted_env)
		return ;
	i = 0;
	while (sorted_env[i])
	{
		if (sorted_env[i][0] == '\0')
			printf("Warning: Empty environment entry at index %d\n", i);
		else
			print_export_line(sorted_env[i]);
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
	shell->last_exit_status = EXIT_SUCCESS;
}

void	handle_export_argument(t_shell *shell, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		shell_error(shell, arg, 10, false);
		shell->last_exit_status = 1;
		return ;
	}
	if (ft_strchr(arg, '='))
		process_export_assignment(shell, arg);
	else
	{
		if (find_env_index(shell->env, arg) == -1)
			env_add(shell, arg);
	}
}

void	ft_export(t_token *cmdargs, t_shell *shell)
{
	t_token	*current;

	current = cmdargs->next;
	if (!current)
		return (print_export(shell));
	while (current)
	{
		handle_export_argument(shell, current->value);
		current = current->next;
	}
}
