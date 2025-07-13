/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:54:01 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/13 16:12:26 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_game(t_game	*game)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game)
		return (1);
	//map parsing and validation
	//game->map = 

	//tmp for testing
	game->map = malloc(sizeof(t_map));
	game->map->no_texture = "/home/user/42/cub3d/textures/wolfenstein/blue_stone.xpm";
	game->map->so_texture = "/home/user/42/cub3d/textures/wolfenstein/color_stone.xpm";
	game->map->ea_texture = "/home/user/42/cub3d/textures/wolfenstein/grey_stone.xpm";
	game->map->we_texture = "/home/user/42/cub3d/textures/wolfenstein/purple_stone.xpm";
	//
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
		return (1); //error message?
	//init game struct;
	if (init_game(game))
		return (free(game), 1); //error message?
	//init graphics;
	init_graphics(game);
	//game_loop
	
	//tmp for testing
	sleep(5);
	return (0);
}

