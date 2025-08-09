/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:48:21 by lshapkin          #+#    #+#             */
/*   Updated: 2025/08/04 12:02:25 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx->mlx_ptr = mlx_init();
	if (!game->mlx->mlx_ptr)
		return (error_msg("Failed to initialize MLX"));
	game->mlx->win_width = WIN_WIDTH;
	game->mlx->win_height = WIN_HEIGHT;
	game->mlx->win_ptr = mlx_new_window(game->mlx->mlx_ptr,
			game->mlx->win_width, game->mlx->win_height, "CUB3D");
	if (!game->mlx->win_ptr)
		return (error_msg("Failed to create window"));
	return (0);
}

int	init_image_buffer(t_game *game)
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
	if (init_mlx(game))
		return (1);
	if (init_image_buffer(game))
		return (1);
	if (validate_textures(game))
		return (1);
	if (load_textures(game))
		return (1);
	init_objects_from_map(game);
	return (0);
}
