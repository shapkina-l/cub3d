
#include "../includes/cub3d.h"

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

