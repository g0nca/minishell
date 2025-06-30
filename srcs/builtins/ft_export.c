/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:36:51 by joaomart          #+#    #+#             */
/*   Updated: 2025/06/30 15:39:22 by ggomes-v         ###   ########.fr       */
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

void	process_export_assignment(t_shell *shell, char *arg)
{
	char	*equal_sign;
	char	*key;
	char	*raw_value;
	char	*clean_value;
	char	*new_env_entry;

	equal_sign = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, equal_sign - arg);
	raw_value = equal_sign + 1;
	clean_value = remove_all_quotes(raw_value);
	new_env_entry = ft_strjoin3(key, "=", clean_value);
	add_or_update_env(shell, new_env_entry);
	free(key);
	free(clean_value);
	free(new_env_entry);
	shell->last_exit_status = 0;
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
		shell->last_exit_status = 0;
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
