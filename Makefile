# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 15:43:00 by nolaeche          #+#    #+#              #
#    Updated: 2025/12/15 18:26:23 by nolaeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Werror -Wextra 

SRCS_DIR = src
INCS_DIR = include

MLX_DIR = $(SRCS_DIR)/minilibx-linux
LIBFT_DIR = $(SRCS_DIR)/libft
PRINTF_DIR = $(SRCS_DIR)/printf


MLX_CFLAGS = -I/usr/include -I$(MLX_DIR) -O3
PRINTF_CFLAGS = -I$(PRINTF_DIR)
LIBFT_CFLAGS = -I$(LIBFT_DIR)
PROJ_CFLAGS = -I$(INCS_DIR)
GNL_CFLAGS = -I$(SRCS_DIR)/getnextline

GNL_FILES = getnextline/get_next_line.c getnextline/get_next_line_utils.c

MLX_LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
PRINTF_LDFLAGS = -L$(PRINTF_DIR) -lftprintf
LIBFT_LDFLAGS = -L$(LIBFT_DIR) -lft

SRCS_FILES = main.c \
			map.c \
			maptester.c \
			maptesteraux.c \
			errors.c \
			freedata.c \
			game.c \
			loadassets.c \
			render.c \
			hooks.c \
			movements.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
SRCS += $(addprefix $(SRCS_DIR)/, $(GNL_FILES))

OBJS = $(SRCS:.c=.o)

all: $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx_Linux.a $(PRINTF_DIR)/libftprintf.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(PRINTF_LDFLAGS) $(LIBFT_LDFLAGS) $(MLX_LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_CFLAGS) $(LIBFT_CFLAGS) $(PROJ_CFLAGS) $(GNL_CFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx_Linux.a:
	@echo "Compilando MiniLibX..."
	@make -C $(MLX_DIR)

$(PRINTF_DIR)/libftprintf.a:
	@make -C $(PRINTF_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@make clean -C $(PRINTF_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@make fclean -C $(PRINTF_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
