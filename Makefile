CC := cc
FLAGS := -Werror -Wextra -Wall -g 
MLXFLAGS := -lX11 -lXext -lz -no-pie -lm
NAME := cub3D
SRC := src/main.c
OBJ := $(SRC:.c=.o)
SRC_BONUS := main_bonus.c
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