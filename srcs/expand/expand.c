/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/17 10:38:08 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expander(t_token *list, t_shell *shell)
{
	/* int i; */
	(void)shell;
	/* i = 0; */
	while (list)
	{
		if (list->value && list->type != TOKEN_SIMPLE_QUOTE)
			list->value = expand_variables(list->value, shell->env);
		list = list->next;
	}	
}

char	*expand_variables(const char *input, char **envp)
{
	char	*result;
	char	*current;

	result = (char *)malloc(calculate_final_size(input, envp) + 1);
	if (!result)
		return (NULL);
	current = result;
	while (*input)
	{
		if (*input == '$' && ft_isalpha(*(input + 1)))
			copy_env_value(&input, &current, envp);
		else
		{
			*current = *input;
			current++;
			input++;
		}
	}
	*current = '\0';
	return (result);
}

void	copy_env_value(const char **input, char **current, char **envp)
{
	char	*var;
	char	*value;
	int		i;

	var = (char *)malloc(sizeof(char *) * ft_strlen(*input));
	if (!var)
		return ;
	(*input)++;
	i = 0;
	while (ft_isalnum(**input) || **input == '_')
		var[i++] = *(*input)++;
	var[i] = '\0';
	value = get_env_value(var, envp);
	free(var);
	if (value)
	{
		while (*value)
			*(*current)++ = *value++;
	}
}

size_t	calculate_final_size(const char *input, char **envp)
{
	size_t	size;

	size = 0;
	while (*input)
	{
		if (*input == '$' && ft_isalpha(*(input + 1)))
			process_env_var(&input, &size, envp);
		else
		{
			size += 1;
			input++;
		}
	}
	return (size);
}

void	process_env_var(const char **input, size_t *size, char **envp)
{
	char	*var;
	char	*value;
	int		i;

	var = (char *)malloc(sizeof(char *) * (ft_strlen(*input)) + 1);
	if (!var)
		return ;
	(*input)++;
	i = 0;
	while (ft_isalnum(**input) || **input == '_')
		var[i++] = *(*input)++;
	var[i] = '\0';
	value = get_env_value(var, envp);
	free(var);
	if (value)
		*size += ft_strlen(value);
}

/* Tokenizer: identifica tokens (comando, argumentos, operadores, etc.)

Expansão: percorre os tokens, e para cada um:

    se não estiver entre aspas simples, expande variáveis $VAR

    se estiver entre aspas duplas, também expande

    se estiver entre aspas simples, não expande

Parsing: organiza os tokens já expandidos em comandos:

    comando principal

    argumentos

    redirecionamentos (>, <, >>, etc.)

    pipes (|)

    operadores (&&, ||, etc. se estiveres a implementar) */