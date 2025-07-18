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

void	initialize_data(t_init *data)
{
	data->no = 0;
	data->so = 0;
	data->we = 0;
	data->ea = 0;
	data->f = 0;
	data->c = 0;
	data->width = 0;
	data->height = 0;
	data->array = NULL;
	data->test_map = NULL;
}

void	initialize_map(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor = (t_color *)malloc(sizeof(t_color));
	map->ceiling = (t_color *)malloc(sizeof(t_color));
	map->map = NULL;
}
