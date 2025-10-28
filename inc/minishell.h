/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:14:44 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/28 12:44:58 by ggomes-v         ###   ########.fr       */
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

extern int	g_exit_status;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_shell
{
	char					**env;
	char					*temp_heredoc_path;
	int						last_exit_status;
	int						running;
	int						heredoc_counter;
	char					*in;
	char					*out;
	char					*append;
	char					*heredoc;
	struct s_token			*token;
	struct s_exec_node		*tree;
	t_list					*heredoc_files;
	pid_t					main_pid;
}							t_shell;

typedef enum e_token_type
{
	TOKEN_WORD, //           words                  // 0
	TOKEN_CMD, //            commands               // 1
	TOKEN_PIPE, //           |                      // 2
	TOKEN_REDIR_IN, //       <                      // 3
	TOKEN_REDIR_OUT, //      >                      // 4
	TOKEN_APPEND, //         >>                     // 5
	TOKEN_HERE_DOC, //       <<                     // 6
	TOKEN_DOUBLE_QUOTE, //   "                      // 7
	TOKEN_SIMPLE_QUOTE, //   '                      // 8
}	t_token_type;

typedef struct s_token
{
	char			*value;
	int				type;
	int				size;
	int				expansion;
	int				dollar_sign;
	int				in_single_quotes; // 1 in '' / 0 out ''
	int				in_double_quotes; // 1 in "" / 0 out ''
	int				type_quotes;
	char			*heredoc_path;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_APPEND,
	HEREDOC,
	NODE_LEFT,
	NODE_RIGHT
}	t_node_type;

typedef struct s_exec_node
{
	t_node_type			type;
	char				**cmd;
	struct s_exec_node	*left;
	struct s_exec_node	*right;
	int					fd_in;
	int					fd_out;
	char				*input_file;
	char				*output_file;
	char				*append_file;
	char				*heredoc;
	char				**heredoc_delimiters;
	char				*last_redir_in;
	int					last_redir_in_type;
	t_token				*tokens;
}						t_exec_node;

typedef struct s_parser
{
	int		i;
	int		pipe_count;
	int		found_content;
}			t_parser;

int			main(int ac, char **av, char **envp);
int			main_auxiliar(char *line, t_shell *shell, t_token *token);

// tokenizer.c ==================================================
t_token		*tokenizer(char *line, t_shell *shell);
void		add_token(t_token *list, char *val, t_token_type type);
void		add_token_to_list(t_token *list, t_token *new_token);
t_token		*create_token(char *val, t_token_type type);
void		add_final_token(t_token *list, char *joined);
//===============================================================

// process_token.c ==============================================
void		process_token(t_token *list, char *line, int *i, t_shell *shell);
void		process_append_token(t_token *list, int *i);
void		process_heredoc_token(t_token *list, int *i, t_shell *shell);
void		process_redir_out_token(t_token *list, int *i);
void		process_redir_in_token(t_token *list, int *i);
//===============================================================

// process_token2.c =============================================
char		*handle_quoted_text(char *line, int *i,
				int *type_quotes, t_token *list);
char		*handle_regular_text(char *line, int *i);
char		*join_word(char *joined, char *word);
void		tokenizer_word(t_token *list, int *i, char *line);
//===============================================================

// process_token3.c =============================================
void		check_command(t_token *list, t_shell *shell);
void		commands(t_token *head, t_shell *shell);
int			check_executable_cmd(t_token *head, t_shell *shell);
//===============================================================

// delete_quotes.c ==============================================
int			delete_quotes(t_token **list, t_shell *shell);
//===============================================================

// expand.c =====================================================
int			expander(t_token **tokens, t_shell *shell);
int			expander2(t_token *list, t_shell *shell);
int			expander3(t_token *list, t_shell *shell);
char		*expand_variables(const char *input, char **envp, t_token *list);
void		input_with_quotes(const char **input, char **current,
				int wich_quote, t_token *list);
void		copy_env_value(const char **input, char **current, char **envp);
char		*get_env_value(const char *name, char **envp);
int			should_skip_expansion(t_token *list, t_shell *shell);
void		handle_double_dollar(const char **input, char **current);
void		handle_question_mark(const char **input, char **current);
void		handle_env_variable_expansion(const char **input,
				char **current, char **envp);
//===============================================================

// calculate_final_size.c =======================================
size_t		handle_dollar(const char **input, char **envp, t_token *list);
size_t		handle_env_variable(const char **input, char **envp);
size_t		calculate_final_size(const char *input, char **envp, t_token *list);
size_t		double_quotes(t_token *list, const char **input);
size_t		simple_quotes(t_token *list, const char **input);
//===============================================================

// env_var_compare.c ============================================
int			compare_env_name(char *env_var, char *token, int start, int end);
int			ft_strcmp_enviroment_variables(char *env_var, char *token);
int			verifiy_enviroment_var(t_shell *shell, char *token);
//int			invalid_env_var(t_token *list, t_shell *shell);
int			remove_old_env_variable(t_token **tokens, t_token *current);
//===============================================================

// execution_tree_main.c=========================================
void		execute_command_tree(t_exec_node *node, t_shell *shell);
//===============================================================

// execution_tree_command.c =====================================
void		execute_tree(t_exec_node *node, t_shell *shell);
void		setup_file_descriptors(t_exec_node *node);
t_token		*create_token_chain(char **cmd);
void		execute_command_node(t_exec_node *node, t_shell *shell);
void		free_cmd(char **cmd);
//===============================================================

// execution_tree_redirect.c ====================================
void		execute_input_redirect(t_exec_node *node, t_shell *shell);
void		execute_output_redirect(t_exec_node *node, t_shell *shell);
//===============================================================

// execution_tree_argv.c ========================================
char		**tokens_to_argv(t_token *start, t_token *end);
//===============================================================

// execute_tree_build_main.c ====================================
t_exec_node	*wrap_with_redirects(t_token *start, t_token *end, t_shell *shell);
t_exec_node	*build_execution_tree(t_token *start, t_token *end, t_shell *shell);
void		free_execution_tree(t_exec_node *node, int flag);
void		cleanup_exec_node(t_exec_node *node);
int			open_input_file(t_exec_node *cmd, char *filename, t_shell *shell);
int			open_output_file(t_exec_node *cmd, char *filename,
				int append, t_shell *shell);
//===============================================================

// execution_tree_build_utils.c =================================
t_token		*find_last_pipe(t_token *start, t_token *end);
t_exec_node	*create_pipe_node(t_token *start, t_token *last_pipe,
				t_token *end, t_shell *shell);
t_node_type	get_redirect_node_type(t_token_type type);
t_exec_node	*create_command_node(t_token *start, t_token *end);
t_exec_node	*build_execution_tree_skip_redirect(t_token *start,
				t_token *redirect, t_token *end);
int			is_redirection_token(t_token_type type);
int			count_arguments(t_token *start, t_token *end);
char		**allocate_command_array(int arg_count);
int			handle_command_token(t_exec_node *node, t_token *current, int *i);
void		skip_redirection_token(t_token **current, t_token *end);
//===============================================================

// execution_tree_build_main_utils.c ============================
int			process_single_redirect(t_token **curr_ptr, t_exec_node *cmd,
				t_shell *shell);
int			handle_heredoc_tree(t_token *curr, t_shell *shell,
				t_exec_node *cmd);
int			handle_input_redirect(t_token *curr, t_exec_node *cmd,
				t_shell *shell);
int			handle_output_redirect(t_token *curr, t_exec_node *cmd,
				t_shell *shell);
int			handle_append_redirect(t_token *curr, t_exec_node *cmd,
				t_shell *shell);
//===================================================================
//execution_tree_build_utils3.c =====================================
int			update_delimiters_array(t_exec_node *cmd, char *new_delimiter);

//===================================================================
//===============================================================

// execute_tree_pipe_helpers.c ==================================
pid_t		fork_right_child(int *pipe_fd, t_exec_node *node,
				t_shell *shell, pid_t left_pid);
pid_t		fork_left_child(int *pipe_fd, t_exec_node *node, t_shell *shell);
void		execute_pipe_node(t_exec_node *node, t_shell *shell);
int			create_pipe_and_check(int *pipe_fd);
//===============================================================

// execute_tree_pipe.c ==========================================
void		setup_pipe_left_child(int *pipe_fd,
				t_exec_node *node, t_shell *shell);
void		setup_pipe_right_child(int *pipe_fd,
				t_exec_node *node, t_shell *shell);
void		handle_pipe_parent(int *pipe_fd, pid_t left_pid,
				pid_t right_pid, t_shell *shell);
//===============================================================

// execute_tree_redirect_utils.c ================================
int			is_redirection(t_token_type type);
int			setup_redirections(t_shell *shell, t_exec_node *node);
//===============================================================

// execute_tree_token_utils.c ===================================
int			count_valid_tokens(t_token *start, t_token *end);
void		cleanup_argv_on_error(char **argv, int count);
void		fill_argv_array(t_token *start, t_token *end,
				char **argv, int *count);
int			add_token_to_argv(char **argv, int i, char *value);
//===============================================================

// syntax_error.c ===============================================
int			check_double_pipes(const char *line, t_shell *shell);
int			check_redirects(const char *line, t_shell *shell);
int			check_heredoc_and_redirect_conflict(const char *line,
				t_shell *shell);
int			check_syntax_errors_main(const char *line, t_shell *shell);
int			is_quote(char c);
int			is_space(char c);
int			is_redirect(char c);
int			skip_quotes(const char *str, int i);
int			skip_spaces(const char *str, int *i);
int			check_starting_pipe(const char *line, t_shell *shell);
int			check_unclosed_quotes(const char *line, t_shell *shell);
//===============================================================

// utils.c ======================================================
int			ternary_operator(t_token *list, char quote);
int			my_wifexited(int status);
int			my_wifsignaled(int status);
int			my_wtermsig(int status);
int			manual_wexitstatus(int status);
//===============================================================

// init_tokens.c ================================================
t_token		*init_token_struct_new_node(t_token *list, t_token_type type);
t_token		*init_token_struct_inicial(t_token *list);
//===============================================================

// free_functions ===============================================
void		free_env(char **env);
void		free_struct(t_shell *shell, int flag);
void		free_tokens(t_token **list);
void		free_sorted_env(int i, char **sorted_env);
void		free_args(char **args);
//===============================================================

// init_shell.c =================================================
char		**copy_env(char **envp);
t_shell		*init_shell(int ac, char **av, char **envp);
//===============================================================

// run_builtin.c ================================================
void		verify_token(t_token *type, t_shell *shell);
void		run_builtin(t_token *cmd, t_shell *shell);
//===============================================================

// builtins/*.c =================================================
//echo:
void		ft_echo(t_token *list, t_shell *shell);
void		ft_print_tokens(t_token *current, t_shell *shell);
int			ft_check_n_flag(t_token **current);
void		ft_skip_redirections(t_token **current);
//pwd:
void		ft_pwd(t_shell *shell);
//cd:
void		ft_cd(t_token *cmdargs, t_shell *shell);
void		sucess_cd(char *old_pwd, t_shell *shell);
void		cd_home(t_shell *shell);
bool		cd_oldpwd(t_shell *shell);
void		cd_val(char *target, t_shell *shell);
char		*cd_getenv(t_shell *shell, const char *name);
int			update_env_var(t_shell *shell, const char *name, const char *value);
int			add_env_var(t_shell *shell, char *new_entry, int env_size);
//env:
void		ft_env(t_shell *shell);
//export:
void		ft_export(t_token *cmdargs, t_shell *shell);
void		handle_export_argument(t_shell *shell, char *arg);
void		process_export_assignment(t_shell *shell, char *arg);
void		print_export(t_shell *shell);
void		print_export_line(char *env_var);
char		*remove_all_quotes(char *value);
char		*ft_strjoin3(char *s1, char *s2, char *s3);
void		handle_export_argument(t_shell *shell, char *arg);
void		process_export_assignment(t_shell *shell, char *arg);
//unset:
void		ft_unset(t_token *cmdargs, t_shell *shell);
void		remove_env_var(t_shell *shell, const char *key);
//env_utils:
void		env_add(t_shell *shell, char *new_var);
char		*get_env_key(const char *str);
int			find_env_index(char **env, const char *key);
void		add_or_update_env(t_shell *shell, char *arg);
bool		is_valid_identifier(const char *str);
int			env_count(char **env);
void		sort_env(char **env, int count);
char		**copy_and_sort_env(t_shell *shell, int *count);
void		init_shlvl(t_shell *shell);
void		set_env_var(t_shell *shell, const char *name, const char *value);
//exit:
void		ft_exit(t_shell *shell, t_token *args);
size_t		ft_strlen_exit(const char *s);
int			too_many_arguments(t_shell *shell);
//===============================================================

//exec.c=========================================================
int			is_builtin(char *cmd);
int			handle_direct_path_shell_error(char *path, t_shell *shell);
void		handle_env_path_execution(char **args, t_shell *shell);
char		*get_path_env(char **env);
int			try_paths(char **args, t_shell *shell, char *path_env);
int			ft_backup_stdio(int *stdin_backup, int *stdout_backup);
void		ft_restore_stdio(int stdin_backup, int stdout_backup);
//===============================================================

//heredoc.c======================================================
void		handle_heredoc(t_token *token, t_shell *shell);
int			process_heredoc(t_token *token, t_shell *shell);
char		*create_heredoc(const char *delimiter, t_shell *shell);
void		cleanup_heredoc_files(t_shell *shell);
void		remove_token(t_token **head, t_token *to_remove);
char		*generate_temp_filename(int i);
int			create_temp_file(char **out_filename);
void		error_heredoc(const char *delimiter);
//=================================================================
int			process_heredocs_in_tree(t_exec_node *node, t_shell *shell);
char		*heredoc_parent(int fd, int status, char *filename, t_shell *shell);
void		heredoc_child(const char *delimiter, int fd,
				t_shell *shell, char *filename);
//===============================================================

//signals.c======================================================
void		setup_signals(void);
void		handle_sigint(int sig);
void		handle_heredoc_sigint(int sig);
void		setup_heredoc_signals(void);
void		restore_main_signals(void);
//===============================================================

//error.c =======================================================
void		shell_error(t_shell *shell, char *str, int error, bool exit_flag);
void		ft_error(int error, char *str, t_shell *shell);
//===============================================================

//EXTRAS ========================================================
void		print_tokens(t_token *list, t_shell *shell);
void		print_exec_tree(t_exec_node *node, int depth);
//===============================================================
#endif
