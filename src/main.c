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

int	main(int arc, char **arv)
{
	t_init		init;
	t_map		map;
	t_player	player;

	if (arc != 2)
		return (ft_printf("Error: one .cub file address argument needed.\n"), 1);
	if (!validate_file_format(arv[1]))
		return (ft_printf("Error: argument must be valid .cub file address.\n"), 1);
	initialize_data(&init);
	if (!create_array(&init, arv[1]))
		return (1);
	if (!validate_cub_elements(&init))
		return (ft_printf("Error: map is invalid.\n"), 1);
	initialize_map(&map);
	if (!set_map_data(&init, &map))
		return (ft_printf("Error: map is invalid.\n"), 1);
	if (!validate_map_chars(&map))
		return (ft_printf("Error: map is invalid.\n"), 1);
	if (!validate_map_chars(&map))
		return (ft_printf("Error: map is invalid.\n"), 1);
	print_map(&map);
	print_test_map(&init);
	if (!validate_map_boundaries(&init))
		return (ft_printf("Error: map is invalid.\n"), 1);
	find_starting_point(&map, &player);
}

int	init_game(t_game	*game)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game)
		return (1);
	//tmp
	game->map = NULL;
	//map parsing and validation
	//game->map = 

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

int	main(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (error_msg("Memory allocation failed"), 1);
	if (init_game(game))
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

