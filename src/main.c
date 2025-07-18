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

	// if (arc != 2)
	// 	return (ft_printf("Error: one .cub file address argument needed.\n"), 1);
	// if (!validate_file_format(arv[1]))
	// 	return (ft_printf("Error: argument must be valid .cub file address.\n"), 1);
	initialize_data(&init);
	if (!create_array(&init, argument))
		return (0);
	if (!validate_cub_elements(&init))
		return (error_msg("Error: map is invalid."), 0);
	initialize_map(game->map);
	if (!set_map_data(&init, game->map))
		return (error_msg("Error: map is invalid."), 0);
	if (!validate_map_chars(game->map))
		return (error_msg("Error: map is invalid."), 0);
	if (!validate_map_chars(game->map))
		return (error_msg("Error: map is invalid."), 0);
	print_map(game->map);
	print_test_map(&init);
	if (!validate_map_boundaries(&init))
		return (error_msg("Error: map is invalid."), 0);
	find_starting_point(game->map, game->player);
	printf("end of file validation\n");
	return (1);
}

// int	main(int arc, char **arv)
// {
// 	t_init		init;
// 	t_map		map;
// 	t_player	player;

// 	if (arc != 2)
// 		return (ft_printf("Error: one .cub file address argument needed.\n"), 1);
// 	if (!validate_file_format(arv[1]))
// 		return (ft_printf("Error: argument must be valid .cub file address.\n"), 1);
// 	initialize_data(&init);
// 	if (!create_array(&init, arv[1]))
// 		return (1);
// 	if (!validate_cub_elements(&init))
// 		return (ft_printf("Error: map is invalid.\n"), 1);
// 	initialize_map(&map);
// 	if (!set_map_data(&init, &map))
// 		return (ft_printf("Error: map is invalid.\n"), 1);
// 	if (!validate_map_chars(&map))
// 		return (ft_printf("Error: map is invalid.\n"), 1);
// 	if (!validate_map_chars(&map))
// 		return (ft_printf("Error: map is invalid.\n"), 1);
// 	print_map(&map);
// 	print_test_map(&init);
// 	if (!validate_map_boundaries(&init))
// 		return (ft_printf("Error: map is invalid.\n"), 1);
// 	find_starting_point(&map, &player);
// }

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

// int game_loop(t_game *game)
// {
// 	//to do
//     update_player(game);
// 	//to do
//     render_frame(game);   
//     return (0);
// }

int argument_validation(int arc, char **arv)
{
	if (arc != 2)
		return (error_msg("Error: one .cub file address argument needed."), 0);
	if (!validate_file_format(arv[1]))
		return (error_msg("Error: argument must be valid .cub file address."), 0);
	return (1);
}

int	main(int arc, char **arv)
{
	t_game	*game;

	if (!argument_validation(arc, arv))
		return(1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (error_msg("Memory allocation failed"), 1);
	if (init_game(game, arv[1]))
		return (error_msg("Data initialization failed"),
			exit_game(game), 1);
	if (init_graphics(game))
		return (error_msg("Graphics initialization failed"),
			exit_game(game), 1);
	//game_loop
	
	//tmp for testing
	sleep(5);
	
	exit_game(game);
	return (0);
}

