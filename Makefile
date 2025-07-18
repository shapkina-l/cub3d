CC := cc
FLAGS := -Werror -Wextra -Wall -g 
# MLXFLAGS := -lX11 -lXext -lz -no-pie -lm
MLXFLAGS = -lmlx -lXext -lX11 -lm
NAME := cub3D
SRC :=	src/main.c src/validation/array_creation.c src/validation/file_validation.c \
		src/validation/init_init.c src/validation/test_matrix.c src/validation/validation_utils.c \
		src/map_init.c src/pc_placement.c src/utils.c src/tmp_testing.c \
		src/graphics/minilibx_init.c src/graphics/setup_events.c src/graphics/textures.c
OBJ := $(SRC:.c=.o)
INCLUDES := libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/ all
	$(CC) $(OBJ) -o $(NAME) $(FLAGS) $(INCLUDES) $(MLXFLAGS)

bonus: $(OBJ_BONUS)
	@make -C libft/ all
	$(CC) $(OBJ_BONUS) -o $(NAME) $(FLAGS) $(INCLUDES) $(MLXFLAGS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	/bin/rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	/bin/rm -f $(NAME)
	@make -C libft/ fclean