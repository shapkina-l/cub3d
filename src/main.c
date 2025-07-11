/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:54:01 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/11 21:51:25 by lshapkin         ###   ########.fr       */
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
	sleep(5);
	return (0);
}

