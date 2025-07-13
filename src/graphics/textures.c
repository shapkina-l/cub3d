/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:10:37 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/13 16:37:54 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx->mlx_ptr, path, &texture->width, &texture->height);
    if (!texture->img)
        return (1);
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
    return (0);
}

int load_textures(t_game *game)
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

