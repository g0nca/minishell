# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andrade <andrade@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 12:00:03 by joaomart          #+#    #+#              #
#    Updated: 2025/04/08 10:45:24 by andrade          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf_fd.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs
SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR = $(SRC_DIR)/objs
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

RM = rm -f
AR = ar rcs

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
