/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:56:14 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/25 16:56:15 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	find_map_dimensions(t_init *data, t_map *map)
{
	int	i;
	int	cur;

	i = 0;
	while (map->map[i])
	{
		cur = ft_strlen(map->map[i]);
		if (cur > data->width)
			data->width = cur;
		i++;
	}
	data->height = i;
}

void	initialize_init(t_init *init)
{
	init->no = 0;
	init->so = 0;
	init->we = 0;
	init->ea = 0;
	init->f = 0;
	init->c = 0;
	init->width = 0;
	init->height = 0;
	init->array = NULL;
	init->test_map = NULL;
}

void	initialize_map(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor = (t_color *)malloc(sizeof(t_color));
	map->floor->r = 0;
	map->floor->g = 0;
	map->floor->b = 0;
	map->ceiling = (t_color *)malloc(sizeof(t_color));
	map->ceiling->r = 0;
	map->ceiling->g = 0;
	map->ceiling->b = 0;
	map->map = NULL;
}
