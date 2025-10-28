/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:51:31 by andrade           #+#    #+#             */
/*   Updated: 2025/10/28 12:25:44 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_export_key(char *arg, char *equal_sign, int *append_mode)
{
	char	*key;

	*append_mode = 0;
	if (equal_sign > arg && *(equal_sign - 1) == '+')
	{
		*append_mode = 1;
		key = ft_substr(arg, 0, (equal_sign - arg) - 1);
	}
	else
		key = ft_substr(arg, 0, equal_sign - arg);
	return (key);
}

static char	*get_clean_value(char *equal_sign)
{
	char	*raw_value;
	char	*clean_value;

	raw_value = equal_sign + 1;
	clean_value = remove_all_quotes(raw_value);
	return (clean_value);
}

static char	*build_new_env_entry(t_shell *shell, char *key,
		char *clean_value, int append_mode)
{
	char	*new_env_entry;
	char	*old_val;
	char	*tmp;

	new_env_entry = NULL;
	if (append_mode)
	{
		old_val = get_env_value(key, shell->env);
		if (old_val)
		{
			tmp = ft_strjoin(old_val, clean_value);
			new_env_entry = ft_strjoin3(key, "=", tmp);
			free(tmp);
		}
		else
			new_env_entry = ft_strjoin3(key, "=", clean_value);
	}
	else
		new_env_entry = ft_strjoin3(key, "=", clean_value);
	return (new_env_entry);
}

void	process_export_assignment(t_shell *shell, char *arg)
{
	char	*equal_sign;
	char	*key;
	char	*clean_value;
	char	*new_env_entry;
	int		append_mode;

	equal_sign = ft_strchr(arg, '=');
	key = get_export_key(arg, equal_sign, &append_mode);
	clean_value = get_clean_value(equal_sign);
	new_env_entry = build_new_env_entry(shell, key, clean_value, append_mode);
	add_or_update_env(shell, new_env_entry);
	free(key);
	free(clean_value);
	free(new_env_entry);
	if (shell->last_exit_status == 0)
		shell->last_exit_status = 0;
}
