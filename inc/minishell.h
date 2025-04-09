/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:14:44 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/09 14:46:41 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "../libs/ft_printf_fd/include/ft_printf_fd.h"
# include <stdio.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef enum e_token_type
{
    TOKEN_WORD,     // words                  // 0
    TOKEN_CMD,      // commands               // 1
    TOKEN_PIPE,     // |                      // 2
    TOKEN_REDIR_IN, // <                      // 3
    TOKEN_REDIR_OUT,// >                      // 4
    TOKEN_APPEND,   // >>                     // 5
    TOKEN_HERE_DOC, // <<                     // 6
    TOKEN_DOUBLE_QUOTE, // "                  // 7
    TOKEN_SIMPLE_QUOTE, // '                  // 8
}   t_token_type;

typedef struct  s_token {
    char            *value;
    int             type;
    struct s_token  *next;
    struct s_token  *prev;
}   t_token;

typedef struct s_token_list
{
    t_token *tokens;
    int size;
    int capacity;
}   t_token_list;

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

void free_tokens(t_token_list *list);
t_token_list *init_token_list(void);
void add_token(t_token_list *list, char *val, t_token_type type);


int     main(int ac, char **av, char **envp);

//APAGAR
void    print_envp(char *line, t_shell *shell);
int    exit_program(char *line, t_shell *shell);
void print_tokens(t_token_list *list);

//  tokenizer.c ==========================================================
void add_token(t_token_list *list, char *val, t_token_type type);
void add_token_to_list(t_token_list *list, t_token *new_token);
t_token *create_token(char *val, t_token_type type);
//========================================================================

// process_token.c ================================================
void process_token(t_token_list *list, char *line, int *i);
void process_append_token(t_token_list *list, int *i);
void process_heredoc_token(t_token_list *list, int *i);
void process_redir_out_token(t_token_list *list, int *i);
void process_redir_in_token(t_token_list *list, int *i);
//==================================================================

// process_token2.c ================================================

t_token_list *tokenizer(char *line);
void tokenizer_word(t_token_list *list, int *i, char *line);
void    check_command(t_token_list *list);
//==================================================================

// init_tokens.c ================================================
t_token_list *init_token_list(void);
t_token_list    init_token_struct(t_token_list *list);
//===============================================================

//  free_functions
void free_env(char **env);
void    free_struct(t_shell *shell);
void free_tokens(t_token_list *list);

//  init_shell.c
char **copy_env(char **envp);
t_shell     *init_shell(int ac, char **av, char **envp);

// run_builtin.c
void	verify_token(t_token_list *type, t_shell *shell);
void	run_builtin(t_token_list *cmd, t_shell *shell);
//===============================================================

// builtins/*.c
void	ft_echo(t_token_list *list, t_shell *shell);
int	is_n_flag(char *arg);
/* void	have_n(t_token_list *list);
int	n_value(char *current); */
//===============================================================

// parser.c
//int     parse_line(char *line);


//      LIBFT
//int	ft_strcmp(char *s1, char *s2);
//char	*ft_strdup(const char *s);


#endif
