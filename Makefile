CC := cc
FLAGS := -Werror -Wextra -Wall -g 
# MLXFLAGS := -lX11 -lXext -lz -no-pie -lm
MLXFLAGS = -lmlx -lXext -lX11 -lm
NAME := cub3D
SRC :=	src/main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		src/array_creation.c src/file_validation.c src/init_init.c src/map_init.c src/pc_placement.c \
		src/test_matrix.c src/utils.c
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
	$(CC) $(FLAGS) -Iget_next_line -c $< -o $@

clean:
	@make -C libft/ clean
	/bin/rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	/bin/rm -f $(NAME)
	@make -C libft/ fclean