# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 14:14:40 by ggomes-v          #+#    #+#              #
#    Updated: 2025/10/28 09:10:20 by joaomart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# VARIABLES
# ==============================================================================

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
READLINE = -lreadline

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = libs/ft_printf_fd
FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf_fd.a

LEAKS_LOG		= ./leaks.log
READLINE_SUPP	= readline.supp
VALGRINDFLAGS	= -s --suppressions=$(READLINE_SUPP) \
				  --tool=memcheck --trace-children=no --leak-check=full \
				  --show-leak-kinds=all --track-origins=yes \

## --trace-children=no
## --child-silent-after-fork=yes

MINISHELL_SRCS = srcs/main.c \
				srcs/free_functions/free.c \
				srcs/free_functions/free2.c \
				srcs/init_shell.c \
				srcs/utils/utils.c \
				srcs/tokenizer/tokenizer.c \
				srcs/tokenizer/process_token.c \
				srcs/tokenizer/process_token2.c \
				srcs/tokenizer/process_token3.c \
				srcs/tokenizer/init_tokens.c \
				srcs/tokenizer/delete_quotes.c \
				srcs/error_functions/errors.c \
				srcs/syntax_error/syntax_error.c \
				srcs/syntax_error/syntax_error2.c \
				srcs/syntax_error/syntax_error3.c \
				srcs/syntax_error/syntax_error4.c \
				srcs/expand/expand.c \
				srcs/expand/expand2.c \
				srcs/expand/expand3.c \
				srcs/expand/calculate_final_size.c \
				srcs/expand/expand_utils.c \
				srcs/expand/expand_utils2.c \
				srcs/run/run_builtin.c \
				srcs/builtins/ft_echo.c \
				srcs/builtins/ft_echo2.c \
				srcs/builtins/ft_pwd.c \
				srcs/builtins/ft_cd.c \
				srcs/builtins/ft_cd2.c \
				srcs/builtins/ft_cd3.c \
				srcs/builtins/ft_export.c \
				srcs/builtins/ft_export2.c \
				srcs/builtins/ft_export3.c \
				srcs/builtins/ft_unset.c \
				srcs/builtins/env_utils.c \
				srcs/builtins/env_utils2.c \
				srcs/builtins/env_utils3.c \
				srcs/builtins/env_utils4.c \
				srcs/builtins/ft_env.c \
				srcs/builtins/ft_exit.c \
				srcs/builtins/ft_exit2.c \
				srcs/exec/exec.c \
				srcs/exec/exec2.c \
				srcs/exec/exec3.c \
				srcs/signals/signals.c \
				srcs/heredoc/heredoc.c \
				srcs/heredoc/heredoc2.c \
				srcs/heredoc/heredoc3.c \
				srcs/heredoc/heredoc4.c \
				srcs/heredoc/process_heredocs.c \
				srcs/binary_tree/execution_tree_argv.c \
				srcs/binary_tree/execution_tree_build_main.c \
				srcs/binary_tree/execution_tree_build_main2.c \
				srcs/binary_tree/execution_tree_build_utils.c \
				srcs/binary_tree/execution_tree_build_utils2.c \
				srcs/binary_tree/execution_tree_build_utils3.c \
				srcs/binary_tree/execution_tree_build_main_utils.c \
				srcs/binary_tree/execution_tree_build_main_utils2.c \
				srcs/binary_tree/execution_tree_build_main_utils3.c \
				srcs/binary_tree/execution_tree_command.c \
				srcs/binary_tree/execution_tree_command2.c \
				srcs/binary_tree/execution_tree_main.c \
				srcs/binary_tree/execution_tree_pipe_helpers.c \
				srcs/binary_tree/execution_tree_pipe.c \
				srcs/binary_tree/execution_tree_redirect_utils.c \
				srcs/binary_tree/execution_tree_token_utils.c

MINISHELL_OBJS_DIR = srcs/objs
MINISHELL_OBJS = $(patsubst srcs/%.c, $(MINISHELL_OBJS_DIR)/%.o, $(MINISHELL_SRCS))

# ==============================================================================
# RULES
# ==============================================================================

all: $(NAME)

$(NAME): $(MINISHELL_OBJS) $(LIBFT) $(FT_PRINTF)
	@echo "$(BOLD_BLUE)╔══════════════════════════════════════╗"
	@echo "$(BOLD_BLUE)║       🔨 Building $(NAME)...       ║"
	@echo "$(BOLD_BLUE)╚══════════════════════════════════════╝$(RESET)"
	@$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBFT) $(FT_PRINTF) $(READLINE) -o $(NAME)
	@echo "$(BOLD_GREEN)✅ $(NAME) built successfully!$(RESET)"

$(MINISHELL_OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🛠️  Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
# ^ Gera um arquivo .o dentro da pasta $(OBJ_DIR) a partir de um .c
# | %.o e %.c -> O Makefile substitui o % pelo nome base do arquivo
# | Exemplo: src/main.c %(OBJ_DIR) definido como build
# | Entao fica build/main.o: src/main.c

$(LIBFT):
	@echo "$(BOLD_BLUE)╔══════════════════════════════════════╗"
	@echo "$(BOLD_BLUE)║        📚 Compiling libft...         ║"
	@echo "$(BOLD_BLUE)╚══════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(BOLD_GREEN)✅ libft.a built successfully!$(RESET)"
# ^ Compila o libft
# | Cria a pasta build/ se nao existir
# | Procura no diretorio do libft todos os ficheiros .o
# | Move os *.o para a pasta build

$(FT_PRINTF):
	@echo "$(BOLD_BLUE)╔══════════════════════════════════════╗"
	@echo "$(BOLD_BLUE)║     🖨️  Compiling ft_printf_fd...     ║"
	@echo "$(BOLD_BLUE)╚══════════════════════════════════════╝$(RESET)"
	@$(MAKE) -C $(FT_PRINTF_DIR) --no-print-directory
	@echo "$(BOLD_GREEN)✅ libftprintf.a built successfully!$(RESET)"

va: $(NAME) sup
	@echo "$(BOLD_BLUE)╔══════════════════════════════════════╗"
	@echo "$(BOLD_BLUE)║        🔍 Running Valgrind...        ║"
	@echo "$(BOLD_BLUE)╚══════════════════════════════════════╝$(RESET)"
	@valgrind $(VALGRINDFLAGS) ./$(NAME)
# --leak-check=full --> Mostra todos os blocos de memoria que
#		nao foram libertados no fim da execucao do programa.
#		Mostra o relatorio detalhado sobre cada leak
#		Indica a linha exata do codigo onde o bloco de memoria foi alocado

# --show-leak-kinds=all --> Mostra os todos os diferentes tipos de leaks
# --track-origins=yes --> Mostra onde o conteudo invalido de memoria comecou

clean:
	@echo "$(BOLD_BLUE)╔══════════════════════════════════════╗"
	@echo "$(BOLD_BLUE)║     🧹 Cleaning object files...      ║"
	@echo "$(BOLD_BLUE)╚══════════════════════════════════════╝$(RESET)"
	@rm -rf $(MINISHELL_OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(FT_PRINTF_DIR) clean --no-print-directory
# ^ Apaga todos os ficheiros .o da pasta Build
# | Mantem o executavel

fclean: clean
	@echo "$(BOLD_BLUE)╔══════════════════════════════════════╗"
	@echo "$(BOLD_BLUE)║         🗑️  Removing all...           ║"
	@echo "$(BOLD_BLUE)╚══════════════════════════════════════╝$(RESET)"
	@rm -rf $(NAME)
	@rm -rf Valgrind
	@rm -rf readline.supp
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean --no-print-directory
# ^ Apaga todos os ficheiros .o da pasta build e o executavel
# | Apaga o arquivo log do Valgrind

re: fclean all

define SUP_BODY
{
   name
   Memcheck:Leak
   fun:*alloc
   ...
   obj:*/libreadline.so.*
   ...
}
{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}
endef

sup:
	$(file > readline.supp,$(SUP_BODY))

.PHONY: all clean fclean re va sup

# Cores #
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
BOLD_BLUE = \033[1;34m
RESET = \033[0m
