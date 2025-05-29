/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:55:23 by andrade           #+#    #+#             */
/*   Updated: 2025/05/29 16:50:40 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Função para processar redirecionamentos de saída
int handle_output_redirection(t_token *token)
{
    t_token *current = token;
    int fd;

    while (current)
    {
        if (current->type == TOKEN_REDIR_OUT && current->next && current->next->value)
        {
            fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("minishell");
                return (1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            return (0);
        }
        else if (current->type == TOKEN_APPEND && current->next && current->next->value)
        {
            fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("minishell");
                return (1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            return (0);
        }
        current = current->next;
    }
    return (0);
}

// Função para processar redirecionamentos de entrada
int handle_input_redirection(t_token *token)
{
    t_token *current = token;
    int fd;

    while (current)
    {
        if (current->type == TOKEN_REDIR_IN && current->next && current->next->value)
        {
            fd = open(current->next->value, O_RDONLY);
            if (fd < 0)
            {
                perror("minishell");
                return (1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            return (0);
        }
        current = current->next;
    }
    return (0);
}

// Setup de redirecionamentos simplificado
int setup_redirections(t_token *token)
{
    if (handle_input_redirection(token) != 0)
        return (1);

    if (handle_output_redirection(token) != 0)
        return (1);

    return (0);
}

// Função para criar um array de argumentos apenas com CMD e WORD
// EXCLUINDO redirecionamentos e seus arquivos
char **create_clean_args(t_token *token)
{
    t_token *current = token;
    char **args;
    int count = 0;
    int i = 0;

    // Contar argumentos válidos (CMD e WORD que não são arquivos de redirecionamento)
    while (current)
    {
        if (current->type == TOKEN_CMD || current->type == TOKEN_WORD)
        {
            // Verificar se não é um arquivo de redirecionamento
            if (current->prev &&
                (current->prev->type == TOKEN_REDIR_OUT ||
                 current->prev->type == TOKEN_REDIR_IN ||
                 current->prev->type == TOKEN_APPEND))
            {
                // Este WORD é um nome de arquivo, pular
                current = current->next;
                continue;
            }
            count++;
        }
        current = current->next;
    }

    // Alocar array
    args = malloc(sizeof(char *) * (count + 1));
    if (!args)
        return (NULL);

    // Preencher array
    current = token;
    while (current && i < count)
    {
        if (current->type == TOKEN_CMD || current->type == TOKEN_WORD)
        {
            // Verificar se não é um arquivo de redirecionamento
            if (current->prev &&
                (current->prev->type == TOKEN_REDIR_OUT ||
                 current->prev->type == TOKEN_REDIR_IN ||
                 current->prev->type == TOKEN_APPEND))
            {
                // Este WORD é um nome de arquivo, pular
                current = current->next;
                continue;
            }
            args[i] = ft_strdup(current->value);
            i++;
        }
        current = current->next;
    }
    args[i] = NULL;

    return (args);
}

// Versão corrigida da execução builtin
void ft_execute_builtin_corrected(t_token *token, t_shell *shell,
                                  int stdin_backup, int stdout_backup)
{
    char **clean_args;

    // Configurar redirecionamentos primeiro
    if (setup_redirections(token) != 0)
    {
        ft_restore_stdio(stdin_backup, stdout_backup);
        return;
    }

    // Criar argumentos limpos (sem redirecionamentos)
    clean_args = create_clean_args(token);
    if (!clean_args)
    {
        ft_restore_stdio(stdin_backup, stdout_backup);
        return;
    }

    // Executar builtin com argumentos limpos
    // Aqui você precisa adaptar sua função run_builtin para aceitar char**
    // Ou criar uma versão que usa o array clean_args
    run_builtin_with_args(clean_args, shell); // Você precisa implementar esta função

    // Limpar memória
    for (int i = 0; clean_args[i]; i++)
        free(clean_args[i]);
    free(clean_args);

    // Restaurar stdio
    ft_restore_stdio(stdin_backup, stdout_backup);
}
