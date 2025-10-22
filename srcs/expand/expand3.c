/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:09:41 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/22 11:10:18 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Processa a entrada quando encontra aspas,
 *   atualizando flags de contexto.
 *
 * Esta função lida com aspas simples e duplas na string de entrada, alternando
 * os estados `in_single_quotes` ou `in_double_quotes` do token atual. Também
 * avança os ponteiros de entrada e de escrita.
 *
 * @param input Ponteiro para a string de entrada (é avançado dentro da função).
 * @param current Ponteiro para o buffer onde a entrada está a ser copiada.
 * @param wich_quote Indica o tipo de aspas encontrado:
 *   1 para aspas simples ('), 2 para aspas duplas (").
 * @param list Ponteiro para o token atual, cujas
 *   flags de aspas serão atualizadas.
 */
void	input_with_quotes(const char **input, char **current,
			int wich_quote, t_token *list)
{
	if (wich_quote == 2)
	{
		list->in_double_quotes = !list->in_double_quotes;
		*(*current)++ = *(*input)++;
	}
	else if (wich_quote == 1)
	{
		list->in_single_quotes = !list->in_single_quotes;
		*(*current)++ = *(*input)++;
	}
}
