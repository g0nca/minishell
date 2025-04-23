/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:59:40 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/23 15:30:57 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	animation(char *mensagem)
{
	int i;
	printf("\n");
	for (i = 0; mensagem[i] != '\0'; i++) {
		printf("%c", mensagem[i]);
	fflush(stdout);  // força o print imediato
	usleep(100000);  // 0.1 segundos (100ms)
	}
}

void	ft_exit(t_shell *shell)
{
		shell->running = 0;
		animation("Leaving Without Leaks :) ");
		free_struct(shell);
}
