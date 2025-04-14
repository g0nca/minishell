/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/14 15:48:58 by ggomes-v         ###   ########.fr       */
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
			list->value = expand_variables(list->value, shell->env);
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

size_t calculate_final_size(const char *input, char **envp)
{
    size_t size;
    const char *p;
    char var[256];
    char *value;
    int i;

    size = 0;
    p = input;
    while (*p)
    {
        if (*p == '$' && ft_isalpha(*(p + 1)))
        {
            p++;
            i = 0;
            while (ft_isalnum(*p) || *p == '_')
                var[i++] = *p++;
            var[i] = '\0';
            value = get_env_value(var, envp);
            if (value)
                size += ft_strlen(value);
        }
        else
        {
            size += 1;
            p++;
        }
    }
    return (size);
}

char *expand_variables(const char *input, char **envp)
{
    const char *p;
    char *result;
    char *current;
    size_t final_size;
    char var[256];
    char *value;
    int i;

    final_size = calculate_final_size(input, envp);
    result = (char *)malloc(final_size + 1);
    if (!result)
        return (NULL);
    current = result;
    p = input;
    while (*p)
    {
        if (*p == '$' && ft_isalpha(*(p + 1)))
        {
            p++;
            i = 0;
            while (ft_isalnum(*p) || *p == '_')
                var[i++] = *p++;
            var[i] = '\0';
            
            value = get_env_value(var, envp);
            if (value)
            {
                while (*value)
                    *current++ = *value++;
            }
        }
        else
        {
            *current = *p;
            current++;
            p++;
        }
    }
    *current = '\0';
    return (result);
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