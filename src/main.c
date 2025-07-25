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

	initialize_init(&init);
	if (!build_array_from_file(&init, argument))
		return (free_init(&init), 0);
	if (!validate_cub_elements(&init))
		return (free_init(&init), 0);
	initialize_map(game->map);
	if (!set_map_data(&init, game->map))
		return (free_init(&init), 0);
	if (!validate_map_chars(game->map))
		return (free_init(&init), 0);
	// print_map(game->map);
	// print_test_map(&init);
	if (!validate_map_boundaries(&init))
		return (free_init(&init), 0);
	// print_test_map(&init);
	find_starting_point(game->map, game->player);
	free_init(&init);
	return (1);
}

int init_game_extra(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (0);
	ft_memset(game->map, 0, sizeof(t_map));

	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (0);
	ft_memset(game->player, 0, sizeof(t_player));
	return (1);
}

// int init_game_extra(t_game	*game)
// {
// 	game->map = malloc(sizeof(t_map));
// 	if (!game->map)
// 		return (0);
// 	game->player = malloc(sizeof(t_player));
// 	if (!game->player)
// 		return (0);
// 	return (1);
// }

int	init_game(t_game	*game, char *argument)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		return (1);
	ft_memset(game->mlx, 0, sizeof(t_mlx));
	init_game_extra(game);
	if (!file_validation(game, argument))
		return (1);
	game->raycast = malloc(sizeof(t_rc));
	if (!game->raycast)
		return(1);
	ft_memset(game->raycast, 0, sizeof(t_rc));
	game->no_texture = malloc(sizeof(t_texture));
	if (!game->no_texture)
		return (1);
	ft_memset(game->no_texture, 0, sizeof(t_texture));
	game->so_texture = malloc(sizeof(t_texture));
	if (!game->so_texture)
		return (1);
	ft_memset(game->so_texture, 0, sizeof(t_texture));
	game->ea_texture = malloc(sizeof(t_texture));
	if (!game->ea_texture)
		return (1);
	ft_memset(game->ea_texture, 0, sizeof(t_texture));
	game->we_texture = malloc(sizeof(t_texture));
	if (!game->we_texture)
		return (1);
	ft_memset(game->we_texture, 0, sizeof(t_texture));
	return (0);
}

// int game_loop(t_game *game)
// {
// 	//to do
//     update_player(game);
// 	//to do
//     raycasting(game);   
//     return (0);
// }

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
	ft_memset(game, 0, sizeof(t_game));
	if (init_game(game, arv[1]))
		return (error_msg("Data initialization failed."),
			exit_game(game), 1);
	if (init_graphics(game))
		return (error_msg("Graphics initialization failed."),
			exit_game(game), 1);
	// fill_screen(game);
	//game_loop
	//tmp for testing
	raycasting(game);
	sleep(10);
	
	exit_game(game);
	return (0);
}

