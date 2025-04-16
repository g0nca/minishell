/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:29:13 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/16 12:35:24 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int     parse_line(t_shell *shell, char *line)
{
    size_t bytes;

    bytes = ft_strlen(line);
    if (bytes > 2097152)
        shell_error(shell, "Argument list too long", 12, EXIT_FAILURE);
    return (1);
}

//Esta funcao serve para checar o numero maximo de caracteres que sao enviados
//e caso ultrapasse retorna uma mensagem de erro
//So deve retornar erro quando e chamado um comando externo usando o execve
//Exemplo
//echo 8Milhoes de '$' -> o bash aceita perfeitamente
// /bin/echo 8Milhoes de '$' -> o bash retorna mensagem de erro porque o execve 
// tem limite maximo de 2 mb
