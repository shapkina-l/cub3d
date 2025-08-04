CC := cc
FLAGS := -Werror -Wextra -Wall -g 
MLXFLAGS := -lX11 -lXext -lz -no-pie -lm
# MLXFLAGS = -lmlx -lXext -lX11 -lm
NAME := cub3D
SRC :=	src/main.c src/validation/base_array_building.c src/validation/file_validation.c \
		src/validation/init_init.c src/validation/test_matrix.c src/validation/validation_utils.c \
		src/validation/validation_utils2.c src/validation/map_init.c src/validation/pc_placement.c src/utils.c \
		src/graphics/minilibx_init.c src/graphics/setup_events.c src/graphics/textures.c src/raycasting/raycasting.c \
		src/raycasting/printing.c src/player.c src/free.c src/validation/validation.c src/raycasting/books.c \
		src/raycasting/book_rendering.c src/raycasting/score.c src/raycasting/win.c src/raycasting/ceiling.c src/minimap.c
OBJ := $(SRC:.c=.o)
INCLUDES := libft/libft.a minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/ all
	@make -C minilibx-linux/ all
	$(CC) $(OBJ) -o $(NAME) $(FLAGS) $(INCLUDES) $(MLXFLAGS)

bonus: $(OBJ_BONUS)
	@make -C libft/ all
	@make -C minilibx-linux/ all
	$(CC) $(OBJ_BONUS) -o $(NAME) $(FLAGS) $(INCLUDES) $(MLXFLAGS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	@make -C minilibx-linux/ clean
	/bin/rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	/bin/rm -f $(NAME)
	@make -C libft/ fclean