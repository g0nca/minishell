/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:24:06 by joaomart          #+#    #+#             */
/*   Updated: 2025/05/28 10:39:13 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Lida com o sinal SIGINT (Ctrl-C) durante a execução do shell.
 *
 * Imprime uma nova linha, limpa a linha atual e redesenha o prompt,
 * permitindo ao utilizador introduzir um novo comando de forma limpa.
 *
 * @param sig Número do sinal (não utilizado).
 */
void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @brief Configura os sinais padrão usados pelo shell.
 *
 * - Captura SIGINT (Ctrl-C) para interromper a
 *   linha atual e mostrar um novo prompt.
 * - Ignora SIGQUIT (Ctrl-\) para evitar que o shell seja encerrado à força.
 */
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
