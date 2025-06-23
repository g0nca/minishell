/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:22:07 by joaomart          #+#    #+#             */
/*   Updated: 2025/06/23 14:00:21 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_path_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}
/* 
bool	handle_absolute_path(char **args, t_shell *shell)
{
	if (ft_strchr(args[0], '/'))
	{
		if (access(args[0], F_OK) == -1)
		{
			shell_error(shell, args[0], 1, false);
			exit(127);
		}
		else if (access(args[0], X_OK) == -1)
		{
			shell_error(shell, args[0], 3, false);
			exit(126);
		}
		exec_with_full_path(args, shell);
		return (true);
	}
	return (false);
}
*/
static void handle_direct_path(char **args, t_shell *shell)
{
    char        *path;
    struct stat path_stat;

    path = args[0];
    // Se o comando não contém '/', então é apenas um nome de comando simples
    // que não foi encontrado na PATH. O erro correto é "command not found".
    if (ft_strchr(path, '/') == NULL)
    {
        shell_error(shell, path, 1, true); // Erro 1: command not found -> exit 127
    }

    // A partir daqui, sabemos que o comando é um caminho.
    // Usamos stat() para verificar a existência e o tipo do ficheiro.
    // Se stat() falhar, o ficheiro ou um dos diretórios no caminho não existe.
    if (stat(path, &path_stat) == -1)
    {
        shell_error(shell, path, 2, true); // Erro 2: No such file or directory -> exit 127
    }

    // Verificamos se o caminho aponta para um diretório.
    // A macro S_ISDIR() opera sobre o campo st_mode da estrutura stat.
    if (S_ISDIR(path_stat.st_mode))
    {
        shell_error(shell, path, 5, true); // Erro 5: Is a directory -> exit 126
    }

    // Se existe e não é um diretório, verificamos a permissão de execução.
    if (access(path, X_OK) == -1)
    {
        shell_error(shell, path, 3, true); // Erro 3: Permission denied -> exit 126
    }

    // Se passou por todas as verificações, é um ficheiro executável.
    execve(path, args, shell->env);
    
    // Se execve falhar, reporta o erro e sai.
    shell_error(shell, path, 3, true);
}
void    handle_env_path_execution(char **args, t_shell *shell)
{
    char    *path_env;
    int     result;

    path_env = get_path_env(shell->env);

	if (!path_env)
    {
        shell_error(shell, args[0], 1, false);
    }
    result = try_paths(args, shell, path_env);
    if (result == 0)
		handle_direct_path(args, shell);
    else
        exit(EXIT_SUCCESS);
}
