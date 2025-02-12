NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRC = mandatory_src/cub3d.c mandatory_src/get_start.c mandatory_src/hooks.c \
      mandatory_src/rotate.c mandatory_src/texture_handling.c mandatory_src/wall_checker.c \
      mandatory_src/player_movement.c mandatory_src/ray_casting.c \
      mandatory_src/horizontal.c mandatory_src/vertical.c mandatory_src/key_hooks.c \
      mandatory_src/parsing/general_utils.c mandatory_src/parsing/map_parsing.c \
      mandatory_src/parsing/parser.c mandatory_src/parsing/parsing_utils.c \
      mandatory_src/parsing/read_file.c

# Object files
OBJ = $(SRC:.c=.o)

# Libraries
X11 = -lXext -lX11 -lm
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx_Linux.a

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
	@$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all libmlx libft clean fclean re