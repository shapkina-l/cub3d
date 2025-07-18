#include "../includes/cub3d.h"

void	set_starting_point(t_map *map, t_player *player, int y, int x)
{
	char	direction;

	player->x = x;
	player->y = y;
	direction = map->map[y][x];
	if (direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
}

void	find_starting_point(t_map *map, t_player *player)
{
	int		i;
	int		j;
	char	c;

	j = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			c = map->map[j][i];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				set_starting_point(map, player, j, i);
				return ;
			}
			i++;
		}
		j++;
	}
}
