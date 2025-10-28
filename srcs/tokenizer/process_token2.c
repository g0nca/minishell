/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:18:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/29 15:10:29 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Tokeniza uma palavra a partir da linha de entrada.
 *
 * Esta função percorre a linha de entrada a partir da posição atual,
 * identificando palavras (com ou sem aspas) até encontrar um separador
 * (`espaço`, `|`, `<`, `>`). As partes são unidas e adicionadas como um novo
 * token à lista.
 *
 * @param list Ponteiro para a lista de tokens
 *   onde a nova palavra será adicionada.
 * @param i Ponteiro para o índice atual na
 *   linha (é atualizado conforme se avança).
 * @param line Linha de entrada a ser analisada.
 */
void	tokenizer_word(t_token *list, int *i, char *line)
{
	char	*word;
	char	*joined;
	int		type_quotes;

	type_quotes = 0;
	joined = NULL;
	if (!list || !i || !line)
		return ;
	while (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			word = handle_quoted_text(line, i, &type_quotes, list);
		else
			word = handle_regular_text(line, i);
		joined = join_word(joined, word);
		if (!joined)
			return ;
	}
	add_final_token(list, joined);
}

/**
 * @brief Extrai uma sequência entre aspas da linha de entrada.
 *
 * Lê e devolve o texto entre aspas (`'` ou `"`), incluindo as próprias aspas.
 * Atualiza o índice `i` para apontar após o fecho das aspas.
 * Também atualiza a flag de tipo de aspas no token.
 *
 * @param line A linha de entrada.
 * @param i Ponteiro para o índice atual (avançado até depois das aspas).
 * @param type_quotes Ponteiro para flag que indica o tipo de aspas encontradas.
 * @param list Ponteiro para o token atual
 *   (usado para atualizar contexto de aspas).
 *
 * @return Uma nova string com o texto entre aspas
 *   (com aspas incluídas). Deve ser libertada com `free()`.
 */
char	*handle_quoted_text(char *line, int *i, int *type_quotes, t_token *list)
{
	char	quote;
	char	*word;
	int		start;
	int		end;

	quote = line[*i];
	*type_quotes = ternary_operator(list, quote);
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
	end = *i;
	word = ft_strndup(&line[start], end - start);
	return (word);
}

/**
 * @brief Extrai uma palavra da linha até encontrar um separador ou aspas.
 *
 * Percorre a linha de entrada a partir do índice atual até encontrar um
 * espaço, pipe (`|`), redirecionador (`<`, `>`), ou aspas (`'`, `"`).
 * Retorna uma nova string com a palavra extraída.
 *
 * @param line A linha de entrada.
 * @param i Ponteiro para o índice atual
 *   (será avançado após a leitura da palavra).
 *
 * @return String recém-alocada com a palavra encontrada.
 *   Deve ser libertada com `free()`.
 */
char	*handle_regular_text(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '|' && line[*i] != '<'
		&& line[*i] != '>' && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	return (ft_strndup(&line[start], *i - start));
}

/**
 * @brief Junta uma nova palavra a uma string já existente.
 *
 * Concatena `joined` com `word`, libertando ambas e retornando a nova string
 * combinada. Se `joined` for NULL, retorna `word`.
 *   Se `word` for NULL, retorna `joined`.
 *
 * @param joined String acumulada até o momento (pode ser NULL).
 * @param word Nova palavra a adicionar (pode ser NULL).
 *
 * @return Nova string com o conteúdo combinado. Deve ser libertada com `free()`.
 */
char	*join_word(char *joined, char *word)
{
	char	*temp;

	if (!word)
		return (joined);
	if (!joined)
		return (word);
	temp = ft_strjoin(joined, word);
	free(joined);
	free(word);
	return (temp);
}
