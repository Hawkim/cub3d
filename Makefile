NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
srcs = srcs/main.c srcs/get_start.c srcs/hooks.c \
      srcs/rotate.c srcs/texture_handling.c srcs/wall_checker.c \
      srcs/player_movement.c srcs/ray_casting.c \
      srcs/horizontal.c srcs/vertical.c srcs/key_hooks.c \
      srcs/parsing/general_utils.c srcs/parsing/map_parsing.c \
      srcs/parsing/parser.c srcs/parsing/parsing_utils.c \
      srcs/parsing/read_file.c

# Object files
OBJ = $(srcs:.c=.o)

# Libraries
X11 = -lXext -lX11 -lm
LIBFT = libft/libft.a
# MLX = minilibx-linux/libmlx_Linux.a

# Rules
$(NAME): libmlx libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(X11) -o $(NAME)

libmlx:
	@if [ ! -f $(MLX) ]; then \
		make -C minilibx-linux/; \
	fi

libft:
	@$(MAKE) -C libft

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C libft clean
# @$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all libmlx libft clean fclean re