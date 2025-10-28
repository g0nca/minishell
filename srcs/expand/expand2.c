/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:29:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/28 09:14:50 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Substitui `$$` pelo PID do processo atual.
 *
 * Esta função trata o caso em que a string de entrada
 *   contém `$$`, indicando que o
 * identificador do processo (PID) deve ser expandido.
 *   Converte o PID atual para uma
 * string e copia-o para o buffer de resultado apontado por `current`.
 *
 * O ponteiro `input` é avançado para além do segundo `$`,
 *   e o valor correspondente ao PID é escrito no buffer `current`.
 *
 * @param input Ponteiro para a string de entrada,
 *   onde o primeiro `$` já foi processado.
 *              Este ponteiro é avançado para consumir o segundo `$`.
 * @param current Ponteiro para o buffer de resultado
 *   onde a string do PID será escrita.
 *                Este ponteiro é atualizado após a escrita.
 *
 * @note A string resultante do PID é alocada dinamicamente
 *   via `ft_itoa` e libertada internamente.
 */
void	handle_double_dollar(const char **input, char **current)
{
	char	*pid_str;
	int		pid;
	int		i;

	pid = 4242;
	pid_str = ft_itoa(pid);
	if (pid_str)
	{
		i = 0;
		while (pid_str[i])
		{
			*(*current)++ = pid_str[i];
			i++;
		}
		free(pid_str);
	}
	(*input)++;
}

void	handle_question_mark(const char **input, char **current)
{
	char	*status_str;
	int		i;

	status_str = ft_itoa(g_exit_status);
	if (status_str)
	{
		i = 0;
		while (status_str[i])
		{
			*(*current)++ = status_str[i];
			i++;
		}
		free(status_str);
	}
	(*input)++;
}

/**
 * @brief Extrai o nome de uma variável de ambiente
 *   a partir da string de entrada.
 *
 * Esta função lê caracteres alfanuméricos ou underscores (`_`)
 *   consecutivos a partir do ponteiro `input`, aloca memória dinamicamente
 *   para armazenar o nome da variável, copia os caracteres e termina a
 *   string com um `\0`. O ponteiro `input` é avançado até ao primeiro
 *   caractere após o nome da variável.
 *
 * Exemplo: Para uma string de entrada `USER_NAME=42`, se o `input`
 *   apontar para `USER_NAME`, a função retornará `"USER_NAME"`
 *   e o `input` passará a apontar para o `=`.
 *
 * @param input Ponteiro para a string de entrada contendo o nome da variável.
 *              Este ponteiro é atualizado para apontar após o nome extraído.
 *
 * @return Um ponteiro para uma nova string alocada contendo o nome da variável,
 *         ou NULL em caso de erro de alocação.
 *
 * @note O valor retornado deve ser libertado manualmente com `free()` após uso.
 */
static char	*extract_variable_name(const char **input)
{
	char		*var;
	int			var_len;
	int			i;
	const char	*tmp;

	tmp = *input;
	var_len = 0;
	i = 0;
	while (ft_isalnum(tmp[var_len]) || tmp[var_len] == '_')
		var_len++;
	var = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!var)
		return (NULL);
	while (i < var_len)
		var[i++] = *(*input)++;
	var[i] = '\0';
	return (var);
}

void	handle_env_variable_expansion(const char **input,
			char **current, char **envp)
{
	char	*var;
	char	*value;
	int		i;

	var = extract_variable_name(input);
	if (!var)
		return ;
	value = get_env_value(var, envp);
	free(var);
	if (value)
	{
		i = 0;
		while (value[i])
			*(*current)++ = value[i++];
	}
}
