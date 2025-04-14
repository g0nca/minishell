/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:25:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/14 12:22:54 by ggomes-v         ###   ########.fr       */
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
			printf("TEST");
			//list->value = expand_variables(list->value, shell->env);
		list = list->next;
	}	
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