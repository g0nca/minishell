/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_final_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:27:38 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/19 11:27:38 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	calculate_final_size(const char *input, char **envp, t_token *list)
{
	size_t	size;

	size = 0;
	while (*input)
	{
		if (*input == '\"' && list->in_single_quotes == 0)
			size += double_quotes(list, &input);
		else if (*input == '\'' && list->in_double_quotes == 0)
			size += simple_quotes(list, &input);
		else if (*input == '$' && list->in_single_quotes == 0)
			size += handle_dollar(&input, envp, list);
		else
		{
			size++;
			input++;
		}
	}
	return (size);
}

size_t	double_quotes(t_token *list, const char **input)
{
	size_t	size;

	size = 0;
	list->in_double_quotes = !list->in_double_quotes;
	size++;
	(*input)++;
	return (size);
}

size_t	simple_quotes(t_token *list, const char **input)
{
	size_t	size;

	size = 0;
	list->in_single_quotes = !list->in_single_quotes;
	size++;
	(*input)++;
	return (size);
}

size_t	handle_dollar(const char **input, char **envp, t_token *list)
{
	size_t	size;

	size = 0;
	if (**input == '$' && !list->in_single_quotes)
	{
		if ((*input)[1] == '\0' || (*input)[1] == ' ')
			return ((*input)++, 1);
		(*input)++;
		if (**input == '$')
		{
			size += 10;
			(*input)++;
		}
		else if (**input == '?')
		{
			size += 5;
			(*input)++;
		}
		else if (ft_isalpha(**input) == 1 || **input == '_')
			size += handle_env_variable(input, envp);
		else
			size += 1;
	}
	return (size);
}

size_t	handle_env_variable(const char **input, char **envp)
{
	const char	*start;
	size_t		var_len;
	char		*var;
	char		*value;
	size_t		size;

	var_len = 0;
	size = 0;
	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
	{
		var_len++;
		(*input)++;
	}
	var = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!var)
		return (0);
	ft_strncpy(var, start, var_len);
	var[var_len] = '\0';
	value = get_env_value(var, envp);
	if (value)
		size = ft_strlen(value);
	free(var);
	return (size);
}
