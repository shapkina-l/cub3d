/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:35:18 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/13 14:10:58 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx->mlx_ptr = mlx_init();
	if (!game->mlx->mlx_ptr)
		return (error_msg("Failed to initialize MLX"));
	game->mlx->win_width = 1024;
	game->mlx->win_height = 768;
	game->mlx->win_ptr = mlx_new_window(game->mlx->mlx_ptr,
			game->mlx->win_width, game->mlx->win_height, "CUB3D");
	if (!game->mlx->win_ptr)
		return (error_msg("Failed to create window"));
	return (0);
}

int init_image_buffer(t_game *game)
{
	game->mlx->img_ptr = mlx_new_image(game->mlx->mlx_ptr,
		game->mlx->win_width, game->mlx->win_height);
	if (!game->mlx->img_ptr)
		return (error_msg("Failed to create image buffer"));
	game->mlx->img_data = mlx_get_data_addr(game->mlx->img_ptr,
			&game->mlx->bpp,
			&game->mlx->line_len,
			&game->mlx->endian);
	if (!game->mlx->img_data)
		return (error_msg("Failed to get image data"));
	return (0);
}

int	init_graphics(t_game *game)
{
	//init mlx
	if (init_mlx(game))
		return (1);
	//init image
	if (init_image_buffer(game))
		return (1);
	//setup events
	if (setup_events(game))
		return (1);
	//load textures
	if (load_textures(game))
		return (1);
	//validate textures
	return (0);
}
