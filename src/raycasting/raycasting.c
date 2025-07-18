#include "../../includes/cub3d.h"

void	wall_height(t_game *game, t_raycasting *rc)
{
	if (rc->side == 0)
		rc->wall_dist = (rc->map_x - game->player->x + (1 - rc->step_x) / 2) / rc->ray_dir_x;
	else
		rc->wall_dist = (rc->map_y - game->player->y + (1 - rc->step_y) / 2) / rc->ray_dir_y;

	rc->line_height = (int)(WIN_HEIGHT / rc->wall_dist);

	rc->draw_start = -rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;

	rc->draw_end = rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_end >= WIN_HEIGHT)
		rc->draw_end = WIN_HEIGHT - 1;

	if (rc->side == 0)
		rc->wall_x = game->player->y + rc->wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = game->player->x + rc->wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
}

void dda(t_game *game, t_raycasting *rc)
{
	while (1)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (game->map->map[rc->map_y][rc->map_x] == '1')
			break;
	}
}

void step_calculation(t_game *game, t_raycasting *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player->x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player->x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player->y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - game->player->y) * rc->delta_dist_y;
	}
}

void raycasting(t_game *game)
{
	int		x;
	int		i;
	double camera_x;
	t_raycasting *rc;

	rc = game->raycast;
	rc->plane_x = -1 * game->player->dir_y;
	rc->plane_y = game->player->dir_x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double)WIN_WIDTH - 1;
		rc->ray_dir_x = game->player->dir_x + rc->plane_x * camera_x;
		rc->ray_dir_y = game->player->dir_y + rc->plane_y * camera_x;
		rc->map_x = (int)game->player->x;
		rc->map_y = (int)game->player->y;
		rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
		rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
		step_calculation(game, rc);
		dda(game, rc);
		wall_height(game, rc);
		i = 0;
		while (i < rc->draw_start)
		{
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, i, 0x0000FF);
			i++;
		}
		i = rc->draw_start;
		while (i < rc->draw_end)
		{
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, i, 0x00FF00);
			i++;
		}
		i = rc->draw_end;
		while (i < WIN_HEIGHT)
		{
			mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, i, 0x0000FF);
			i++;
		}
		x++;
	}
}