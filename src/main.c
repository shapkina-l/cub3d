#include "../includes/cub3d.h"


void	print_map(t_map *map)
{
	int	j;

	printf("map:\n");
	j = 0;
	while (map->map[j])
	{
		printf("%s\n", map->map[j]);
		j++;
	}
}

void	print_test_map(t_init *init)
{
	int	j;

	printf("test map:\n");
	j = 0;
	while (init->test_map[j])
	{
		printf("%s\n", init->test_map[j]);
		j++;
	}
}

int	file_validation(t_game	*game, char *argument)
{
	t_init		init;

	initialize_data(&init);
	if (!build_array_from_file(&init, argument))
		return (0);
	if (!validate_cub_elements(&init))
		return (0);
	initialize_map(game->map);
	if (!set_map_data(&init, game->map))
		return (0);
	if (!validate_map_chars(game->map))
		return (0);
	// print_map(game->map);
	// print_test_map(&init);
	if (!validate_map_boundaries(&init))
		return (0);
	// print_test_map(&init);
	find_starting_point(game->map, game->player);
	free_init(&init);
	return (1);
}

int init_game_extra(t_game	*game)
{
	t_init		*init;

	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (0);
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (0);
	init = malloc(sizeof(t_init));
	if (!init)
		return (0);
	return (1);
}

int	init_game(t_game	*game, char *argument)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game)
		return (1);
	init_game_extra(game);
	if (!file_validation(game, argument))
		return (1);
	game->raycast = malloc(sizeof(t_raycasting));
	if (!game->raycast)
		return(1);
	game->no_texture = malloc(sizeof(t_texture));
	if (!game->no_texture)
		return (1);
	game->so_texture = malloc(sizeof(t_texture));
	if (!game->so_texture)
		return (1);
	game->ea_texture = malloc(sizeof(t_texture));
	if (!game->ea_texture)
		return (1);
	game->we_texture = malloc(sizeof(t_texture));
	if (!game->we_texture)
		return (1);
	return (0);
}

void update_player(t_game *game)
{
	double move_speed = 0.1;
	double rot_speed = 0.05;

	move_speed = 0.1;
	rot_speed = 0.05;
	if (game->player->move_forward == 1)
	{
		game->player->x += game->player->dir_x * move_speed;
		game->player->y += game->player->dir_y * move_speed;
	}
	if (game->player->move_backward == 1)
	{
		game->player->x -= game->player->dir_x * move_speed;
		game->player->y -= game->player->dir_y * move_speed;
	}
	if (game->player->move_left == 1)
	{
		game->player->x -= game->player->dir_y * move_speed;
		game->player->y += game->player->dir_x * move_speed;
	}
	if (game->player->move_right == 1)
	{
		game->player->x += game->player->dir_y * move_speed;
		game->player->y -= game->player->dir_x * move_speed;
	}
	if (game->player->rotate_left == 1)
	{
		double old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(rot_speed) - game->player->dir_y * sin(rot_speed);
		game->player->dir_y = old_dir_x * sin(rot_speed) + game->player->dir_y * cos(rot_speed);
	
		double old_plane_x = game->raycast->plane_x;
		game->raycast->plane_x = game->raycast->plane_x * cos(rot_speed) - game->raycast->plane_y * sin(rot_speed);
		game->raycast->plane_y = old_plane_x * sin(rot_speed) + game->raycast->plane_y * cos(rot_speed);
	}
	if (game->player->rotate_right == 1)
	{
		double old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-rot_speed) - game->player->dir_y * sin(-rot_speed);
		game->player->dir_y = old_dir_x * sin(-rot_speed) + game->player->dir_y * cos(-rot_speed);

		double old_plane_x = game->raycast->plane_x;
		game->raycast->plane_x = game->raycast->plane_x * cos(-rot_speed) - game->raycast->plane_y * sin(-rot_speed);
		game->raycast->plane_y = old_plane_x * sin(-rot_speed) + game->raycast->plane_y * cos(-rot_speed);
	}
}

int game_loop(t_game *game)
{
	update_player(game);
	raycasting(game);
    return (0);
}

int argument_validation(int arc, char **arv)
{
	if (arc != 2)
		return (error_msg("One .cub file address argument needed."), 0);
	if (!validate_file_format(arv[1]))
		return (error_msg("Argument must be valid .cub file address."), 0);
	return (1);
}

void	fill_screen(t_game *game)
{
	int	j;
	int	i;

	j = 0;
	while(j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, i, j, 0x00FF00);
			i++;
		}
		j++;
	}
}

int	main(int arc, char **arv)
{
	t_game	*game;

	if (!argument_validation(arc, arv))
		return(1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (error_msg("Memory allocation failed."), 1);
	if (init_game(game, arv[1]))
		return (error_msg("Data initialization failed."),
			exit_game(game), 1);
	if (init_graphics(game))
		return (error_msg("Graphics initialization failed."),
			exit_game(game), 1);
	setup_events(game);
	
	// Start the MLX event loop (this will call game_loop repeatedly)
	mlx_loop(game->mlx->mlx_ptr);
	exit_game(game);
	return (0);
}

