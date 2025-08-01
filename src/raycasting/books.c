
#include "../../includes/cub3d.h"

void	init_objects_from_map(t_game *game)
{
	int	i;
	int	j;

	game->object_count = 0;
	game->score = 0;
	i = 0;
	while (game->map->map[i] && game->object_count < MAX_OBJECTS)
	{
		j = 0;
		while (game->map->map[i][j] && game->object_count < MAX_OBJECTS)
		{
			if (game->map->map[i][j] == 'B')
			{
				game->objects[game->object_count].x = j + 0.5;
				game->objects[game->object_count].y = i + 0.5;
				game->objects[game->object_count].active = 1;
				game->object_count++;
				game->map->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	calculate_object_distances(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < game->object_count)
	{
		if (game->objects[i].active)
		{
			dx = game->objects[i].x - game->player->x;
			dy = game->objects[i].y - game->player->y;
			game->objects[i].distance = dx * dx + dy * dy;
		}
		i++;
	}
}

void	sort_objects_by_distance(t_game *game)
{
	int			i;
	int			j;
	t_object	temp;

	i = 0;
	while (i < game->object_count - 1)
	{
		j = 0;
		while (j < game->object_count - i - 1)
		{
			if (game->objects[j].active && game->objects[j + 1].active
				&& game->objects[j].distance < game->objects[j + 1].distance)
			{
				temp = game->objects[j];
				game->objects[j] = game->objects[j + 1];
				game->objects[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	check_object_collection(t_game *game)
{
	int		i;
	double	collection_distance;
	double	dx;
	double	dy;
	double	distance;

	collection_distance = 0.9;
	i = 0;
	while (i < game->object_count)
	{
		if (game->objects[i].active)
		{
			dx = game->objects[i].x - game->player->x;
			dy = game->objects[i].y - game->player->y;
			distance = sqrt(dx * dx + dy * dy);
			if (distance < collection_distance)
			{
				game->objects[i].active = 0;
				game->score += 10;
				printf("Object collected! Score: %d\n", game->score);
			}
		}
		i++;
	}
}

void	render_objects(t_game *game)
{
	int	i;

	calculate_object_distances(game);
	sort_objects_by_distance(game);
	i = 0;
	while (i < game->object_count)
	{
		if (game->objects[i].active)
		{
			render_object_sprite(game, &game->objects[i]);
		}
		i++;
	}
}
