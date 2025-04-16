/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/16 13:07:04 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expander(t_token *list, t_shell *shell)
{
	int i;
	(void)shell;
	i = 0;
	while (list)
	{
		if (list->value && list->type != TOKEN_SIMPLE_QUOTE)
			list->value = expand_variables(list->value, shell->env, shell);
		list = list->next;
	}	
}

char *get_env_value(const char *name, char **envp)
{
    int len;
	int i;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
    while (envp[i]) 
	{
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
		i++;
    }
    return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:45:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/16 13:45:27 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_env_var(const char **input, size_t *size, char **envp)
{
	char	var[1024];
	char	*value;
	int		i;

	(*input)++;
	i = 0;
	while (ft_isalnum(**input) || **input == '_')
		var[i++] = *(*input)++;
	var[i] = '\0';
	value = get_env_value(var, envp);
	if (value)
		*size += ft_strlen(value);
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

void	copy_env_value(const char **input, char **current, char **envp)
{
	char	var[1024];
	char	*value;
	int		i;

	(*input)++;
	i = 0;
	while (ft_isalnum(**input) || **input == '_')
		var[i++] = *(*input)++;
	var[i] = '\0';
	value = get_env_value(var, envp);
	if (value)
	{
		while (*value)
			*(*current)++ = *value++;
	}
}

char	*expand_variables(const char *input, char **envp, t_shell *shell)
{
	char	*result;
	char	*current;

	(void)shell;
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
/* 
size_t calculate_final_size(const char *input, char **envp)
{
    size_t size;
    char var[1024];
    char *value;
    int i;

    size = 0;
    while (*input)
    {
        if (*input == '$' && ft_isalpha(*(input + 1)))
        {
            input++;
            i = 0;
            while (ft_isalnum(*input) || *input == '_')
                var[i++] = *input++;
            var[i] = '\0';
            value = get_env_value(var, envp);
            if (value)
                size += ft_strlen(value);
        }
        else
        {
            size += 1;
            input++;
        }
    }
    return (size);
}

char *expand_variables(const char *input, char **envp, t_shell *shell)
{
    char *result;
    char *current;
    char enviroment_var[1024];
    char *value;
    int i;
    (void)shell;

    result = (char *)malloc(calculate_final_size(input, envp) + 1);
    if (!result)
        return (NULL);
    current = result;
    while (*input)
    {
        if (*input == '$' && ft_isalpha(*(input + 1)))
        {
            input++;
            i = 0;
            while (ft_isalnum(*input) || *input == '_')
                enviroment_var[i++] = *input++;
            enviroment_var[i] = '\0';
            value = get_env_value(enviroment_var, envp);
            if (value)
            {
                while (*value)
                    *current++ = *value++;
            }
        }
        else
        {
            *current = *input;
            current++;
            input++;
        }
    }
    *current = '\0';
    return (result);
} */


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