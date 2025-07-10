/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:35:18 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/10 13:13:56 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx->mlx_ptr = mlx_init();
	if (!game->mlx->mlx_ptr)
		return (1); //error message?
	game->mlx->win_width = 1024;
	game->mlx->win_height = 768;
	game->mlx->win_ptr = mlx_new_window(game->mlx->mlx_ptr,
			game->mlx->win_width, game->mlx->win_height, "CUB3D");
	if (!game->mlx->win_ptr)
		return (1); //error message?
	return (0);
}

int	init_graphics(t_game *game)
{
	//init mlx
	init_mlx(game);
	//init image
	//setup events
	//load textures
	//validate textures
	return (0);
}
