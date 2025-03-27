# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 14:14:40 by ggomes-v          #+#    #+#              #
#    Updated: 2025/03/27 12:03:30 by ggomes-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yourname <your@email.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 00:00:00 by yourname          #+#    #+#              #
#    Updated: 2025/03/26 00:00:00 by yourname         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# VARIABLES
# ==============================================================================

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

LIBFT_DIR   = lib/libft
LIBFT_A     = $(LIBFT_DIR)/libft.a
OBJ_DIR		= build
READLINE    = -lreadline

INCLUDES    = -I$(LIBFT_DIR) -Iincludes

# Adicione manualmente seus arquivos .c aqui:
SRCS        = src/main.c \
              #src/tokens.c\

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ==============================================================================
# RULES
# ==============================================================================

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(READLINE) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
# ^ Gera um arquivo .o dentro da pasta $(OBJ_DIR) a partir de um .c
# | %.o e %.c -> O Makefile substitui o % pelo nome base do arquivo
# | Exemplo: src/main.c %(OBJ_DIR) definido como build
# | Entao fica build/main.o: src/main.c

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)
	mkdir -p $(OBJ_DIR)/libft
	find $(LIBFT_DIR) -name "*.o" -exec mv {} $(OBJ_DIR)/libft/ \;
# ^ Compila o libft
# | Cria a pasta build/ se nao existir
# | Procura no diretorio do libft todos os ficheiros .o
# | Move os *.o para a pasta build


valgrind: $(NAME)
	valgrind --leak-check=full \
	--track-fds=yes --track-origins=yes \
    --log-file=Valgrind/...   \
	./$(NAME)
# --leak-check=full --> Mostra todos os blocos de memoria que 
#       nao foram libertados no fim da execucao do programa.
#       Mostra o relatorio detalhado sobre cada leak
#       Indica a linha exata do codigo onde o bloco de memoria foi alocado

# --show-leak-kinds=all --> Mostra os todos os diferentes tipos de leaks
# --track-origins=yes --> Mostra onde o conteudo invalido de memoria comecou

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)/libft
	rm -rf $(OBJ_DIR)/src
# ^ Apaga todos os ficheiros .o da pasta Build
# | Mantem o executavel

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)/libft
	rm -rf $(OBJ_DIR)/src
# ^ Apaga todos os ficheiros .o da pasta build e o executavel
# | 

re: fclean all

.PHONY: all clean fclean re
