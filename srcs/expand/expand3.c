/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:09:41 by joaomart          #+#    #+#             */
/*   Updated: 2025/10/28 09:13:01 by joaomart         ###   ########.fr       */
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

/**
 * @brief Expande uma variável de ambiente
 *   e copia o seu valor para o buffer de resultado.
 *
 * Esta função analisa a variável a partir do ponteiro `input`,
 *   determina o tipo de expansão
 * (como `$$`, `$?`, ou `$VAR`), e copia o valor correspondente
 *   para o buffer apontado por `current`.
 * O ponteiro `input` é avançado até depois do nome da variável.
 *
 * Comportamentos suportados:
 * - `$$` : substituído pelo PID atual.
 * - `$?` : substituído pelo código de saída da última execução.
 * - `$!` : expandido para vazio (não implementado em minishell).
 * - `$0-9` : expandido para vazio (parâmetros posicionais não suportados).
 * - `$VAR` : substituído pelo valor da variável de ambiente `VAR`.
 * - Qualquer outro caractere após `$` é tratado
 *   como literal e apenas o `$` é copiado.
 *
 * @param input Ponteiro para a string de entrada contendo
 *   o símbolo `$` seguido do nome da variável.
 * Este ponteiro é atualizado internamente para
 *   apontar após a variável processada.
 * @param current Ponteiro para o buffer de resultado
 *   onde o valor expandido será escrito.
 * Este ponteiro é avançado após a escrita.
 * @param envp Array de strings com as variáveis de
 *   ambiente no formato "VAR=valor".
 */
static int	handle_special_dollar(const char **input, char **current)
{
	if (**input == '$')
	{
		handle_double_dollar(input, current);
		return (1);
	}
	if (**input == '?')
	{
		handle_question_mark(input, current);
		return (1);
	}
	if (**input == '!' || ft_isdigit(**input))
	{
		(*input)++;
		return (1);
	}
	return (0);
}

static int	handle_env_chars(const char **input, char **current, char **envp)
{
	if (ft_isalpha(**input) || **input == '_')
	{
		handle_env_variable_expansion(input, current, envp);
		return (1);
	}
	return (0);
}

void	copy_env_value(const char **input, char **current, char **envp)
{
	(*input)++;
	if (handle_special_dollar(input, current))
		return ;
	if (handle_env_chars(input, current, envp))
		return ;
	*(*current)++ = '$';
}
