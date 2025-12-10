# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 17:25:38 by nolaeche          #+#    #+#              #
#    Updated: 2025/12/03 11:34:47 by nolaeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
INCLUDES = -Iinclude -I../libft
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
AR = ar rcs

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = src/ft_printf.c \
	  src/ft_hexadecimals.c \
	  src/ft_put.c \
	  src/ft_unsigned.c \
	  src/ft_void.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	$(AR) $(NAME) $(OBJ)

clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

