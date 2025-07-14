/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:10:37 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/14 13:51:16 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx->mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	return (0);
}

int	load_textures(t_game *game)
{
	if (load_texture(game, game->no_texture, game->map->no_texture))
		return (1);
	if (load_texture(game, game->so_texture, game->map->no_texture))
		return (1);
	if (load_texture(game, game->ea_texture, game->map->no_texture))
		return (1);
	if (load_texture(game, game->we_texture, game->map->no_texture))
		return (1);
	return (0);
}

int	validate_texture(char *path)
{
	int	fd;

	if (!path)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	if (ft_strlen(path) < 4)
		return (1);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
		return (1);
	return (0);
}

int	validate_textures(t_game *game)
{
	if (!game->map || validate_texture(game->map->no_texture))
		return (1);
	if (!game->map || validate_texture(game->map->no_texture))
		return (1);
	if (!game->map || validate_texture(game->map->no_texture))
		return (1);
	if (!game->map || validate_texture(game->map->no_texture))
		return (1);
	return (0);
}
