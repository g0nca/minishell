# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 12:00:03 by joaomart          #+#    #+#              #
#    Updated: 2025/04/08 16:38:17 by joaomart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf_fd.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs
SRCS = srcs/ft_printf_fd.c srcs/ft_print_format_fd.c srcs/ft_putchar_fd.c \
		srcs/ft_putstr_fd.c srcs/ft_putnbr_fd.c srcs/ft_putunbr_fd.c srcs/ft_puthexa_fd.c \
		srcs/ft_putptr_fd.c

OBJ_DIR = $(SRC_DIR)/objs
OBJS = $(patsubst srcs/%.c, $(OBJ_DIR)/%.o, $(SRCS))

RM = rm -f
AR = ar rcs

all: $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(OBJ_DIR)

re: clean all

.PHONY: all clean fclean re
