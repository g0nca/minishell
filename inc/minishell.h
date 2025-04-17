/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:14:44 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/17 10:46:35 by andrade          ###   ########.fr       */
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
# include <stdbool.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef enum e_token_type
{
    TOKEN_WORD,         // words                  // 0
    TOKEN_CMD,          // commands               // 1
    TOKEN_PIPE,         // |                      // 2
    TOKEN_REDIR_IN,     // <                      // 3
    TOKEN_REDIR_OUT,    // >                      // 4
    TOKEN_APPEND,       // >>                     // 5
    TOKEN_HERE_DOC,     // <<                     // 6
    TOKEN_DOUBLE_QUOTE, // "                      // 7
    TOKEN_SIMPLE_QUOTE, // '                      // 8
}   t_token_type;

typedef struct  s_token {
    char            *value;
    int             type;
    int             size;
    int             type_quotes; // type of quotes "" or '' 0 -> Sem aspas
    struct s_token  *next;                          // 1 -> Aspas Simples ''
    struct s_token *prev;                           // 2 -> Aspas Duplas ""
}   t_token;

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
int     main_auxiliar(char *line, t_shell *shell, t_token *token);

//  tokenizer.c ====================================================
t_token *tokenizer(char *line);
void add_token(t_token *list, char *val, t_token_type type);
void add_token_to_list(t_token *list, t_token *new_token);
t_token *create_token(char *val, t_token_type type);
void add_final_token(t_token *list, char *joined, int type_quotes);
//========================================================================

// process_token.c ================================================
void process_token(t_token *list, char *line, int *i);
void process_append_token(t_token *list, int *i);
void process_heredoc_token(t_token *list, int *i);
void process_redir_out_token(t_token *list, int *i);
void process_redir_in_token(t_token *list, int *i);
//==================================================================

// process_token2.c ===============================================
char *handle_quoted_text(char *line, int *i, int *type_quotes, t_token *list);
char *handle_regular_text(char *line, int *i);
char *join_word(char *joined, char *word);
void tokenizer_word(t_token *list, int *i, char *line);
// ================================================================

// process_token3.c ================================================
void    check_command(t_token *list);
void	commands(t_token *head);
//==================================================================

// expand.c ========================================================
void	expander(t_token *list, t_shell *shell);
char	*expand_variables(const char *input, char **envp);
void	copy_env_value(const char **input, char **current, char **envp);
size_t	calculate_final_size(const char *input, char **envp);
void	process_env_var(const char **input, size_t *size, char **envp);
//==================================================================

// expand2.c =======================================================
char *get_env_value(const char *name, char **envp);
//==================================================================

// syntax_error.c ==================================================
int	is_quote(char c);
int	skip_quote(const char *str, int i);
int	skip_spaces(const char *str, int i);
int	check_unclosed_quotes(const char *str, t_shell *shell);
int	check_syntax_errors(const char *str, t_shell *shell);
//==================================================================

// utils1.c ========================================================
int		ternary_operator(t_token *list, char quote);
//=================================================================

// init_tokens.c ================================================
t_token    init_token_struct(t_token *list);
//===============================================================

//  free_functions ================================================
void free_env(char **env);
void    free_struct(t_shell *shell);
void free_tokens(t_token *list);
//=================================================================
//===============================================================

//  init_shell.c ==================================================
char **copy_env(char **envp);
t_shell     *init_shell(int ac, char **av, char **envp);
//=================================================================
//===============================================================

// run_builtin.c ==================================================
void	verify_token(t_token *type, t_shell *shell);
void	run_builtin(t_token *cmd, t_shell *shell);
//=================================================================

// builtins/*.c ===================================================
void	ft_echo(t_token *list, t_shell *shell);
int	is_n_flag(char *arg);
void	ft_pwd(t_shell *shell);
void	ft_cd(t_token *cmdargs, t_shell *shell);
void	cd_home(t_shell *shell);
/* void	cd_oldpwd(t_shell *shell); */
void	cd_val(char *target, t_shell *shell);
int	update_env_var(t_shell *shell, const char *name, const char *value);
char *cd_getenv(t_shell *shell, const char *name);
void	ft_env(t_shell *shell);
//=================================================================

//error.c =========================================================
void	shell_error(t_shell *shell, char *str, int error, bool exit_flag);
void	ft_error(int error, char *str);
//=================================================================
/* void	have_n(t_token *list);
int	n_value(char *current); */
//===============================================================

// parser.c
int     parse_line(t_token *shell, char *line);

//EXTRAS ==========================================================
int    exit_program(char *line, t_shell *shell);
void    animation(char *mensagem);
void print_tokens(t_token *list, t_shell *shell);
//========================================================================

#endif
