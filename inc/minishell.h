/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:14:44 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/03 15:05:17 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../lib/libft/libft.h"
#include <ctype.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>


# define COMMAND 1
# define W_SPACE 2
# define D_QUOTE 3
# define S_QUOTE 4
# define PIPE 5
# define REDIR_IN 6
# define REDIR_OUT 7
# define APPEND 8
# define HEREDOC 9
# define ENV 10
# define FILE 11

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_token {
    char            *value;
    int             type;
    struct s_token  *next;
    struct s_token *prev;
}   t_token;

typedef struct s_cmd
{
    char **args;
}   t_cmd;

typedef struct s_shell
{
    char **env;
    int last_exit_status;
    int running;
}   t_shell;
// last_exit_status serve para guardar o codigo de saida do ultimo comando
// executado no shell | EXEMPLO :
// --> Se fizermos ls "arquivo existente" o comando sera executado corretamente
// em seguida se fizermos echo $? mostra nos esse codigo de saida que sera 0
// -------------------------------------------------------------------------
// --> Se fizermos ls "arquivo que nao existe" o comando mostra uma mensagem de erro
// echo $? ira mostrar 1 porque houve um erro na execucao do comando anterior


int     main(int ac, char **av, char **envp);

//APAGAR
void    print_envp(char *line, t_shell *shell);
int    exit_program(char *line, t_shell *shell);

//  free_functions
void free_env(char **env);
void    free_struct(t_shell *shell);

//  init_shell.c
char **copy_env(char **envp);
t_shell     *init_shell(int ac, char **av, char **envp);



//      LIBFT
//int	ft_strcmp(char *s1, char *s2);
//char	*ft_strdup(const char *s);



#endif