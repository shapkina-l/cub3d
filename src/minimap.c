/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:46:22 by lshapkin          #+#    #+#             */
/*   Updated: 2025/08/04 12:46:32 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_minimap(t_game *game)
{
	game->minimap = malloc(sizeof(t_minimap));
	if (!game->minimap)
		return (1);
	game->minimap->size = TILE_SIZE;
	game->minimap->space_texture = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			SPACE_TEXT, &game->minimap->size, &game->minimap->size);
	if (!game->minimap->space_texture)
		return (1);
	game->minimap->wall_texture = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			WALL_TEXT, &game->minimap->size, &game->minimap->size);
	if (!game->minimap->wall_texture)
		return (1);
	game->minimap->char_texture = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			CHAR_TEXT, &game->minimap->size, &game->minimap->size);
	if (!game->minimap->char_texture)
		return (1);
	return (0);
}

void	paint_minimap_tile(t_game *game, int j, int i)
{
	if (game->map->map[j][i] == '1')
		mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
			game->minimap->wall_texture, i * TILE_SIZE, j * TILE_SIZE);
	if (game->map->map[j][i] == '0' || game->map->map[j][i] == ' '
			|| game->map->map[j][i] == 'S' || game->map->map[j][i] == 'N'
				|| game->map->map[j][i] == 'E' || game->map->map[j][i] == 'W')
		mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
			game->minimap->space_texture, i * TILE_SIZE, j * TILE_SIZE);
}

void	paint_minimap(t_game *game)
{
	int		i;
	int		j;

	j = 0;
	while (game->map->map[j])
	{
		i = 0;
		while (game->map->map[j][i])
		{
			paint_minimap_tile(game, j, i);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->minimap->char_texture, (game->player->x * TILE_SIZE) - 5,
		(game->player->y * TILE_SIZE) - 5);
}

void	free_minimap(t_game	*game)
{
	if (game->minimap->space_texture)
		mlx_destroy_image(game->mlx->mlx_ptr, game->minimap->space_texture);
	if (game->minimap->wall_texture)
		mlx_destroy_image(game->mlx->mlx_ptr, game->minimap->wall_texture);
	if (game->minimap->char_texture)
		mlx_destroy_image(game->mlx->mlx_ptr, game->minimap->char_texture);
	free(game->minimap);
}
