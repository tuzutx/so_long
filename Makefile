# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nolaeche <nolaeche@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 15:43:00 by nolaeche          #+#    #+#              #
#    Updated: 2025/10/16 15:44:51 by nolaeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Werror -Wextra

MLX_DIR = minilibx-linux
LIBFT_DIR = libft

MLX_CFLAGS = -I/usr/include -I$(MLX_DIR) -O3
LIBFT_CFLAGS = -I$(LIBFT_DIR)

MLX_LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
LIBFT_LDFLAGS = -L$(LIBFT_DIR) -lft

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx_Linux.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_LDFLAGS) $(LIBFT_LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_CFLAGS) $(LIBFT_CFLAGS) -c $< -o $@


$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx_Linux.a:
	@echo "Compilando MiniLibX..."
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
