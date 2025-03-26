# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 14:14:40 by ggomes-v          #+#    #+#              #
#    Updated: 2025/03/26 16:29:21 by ggomes-v         ###   ########.fr        #
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
READLINE    = -lreadline

INCLUDES    = -I$(LIBFT_DIR) -Iincludes

# Adicione manualmente seus arquivos .c aqui:
SRCS        = src/main.c \
              #src/tokens.c\

OBJS        = $(SRCS:.c=.o)

# ==============================================================================
# RULES
# ==============================================================================

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(READLINE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

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

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
