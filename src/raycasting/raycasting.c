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

void	printing_column(t_game *game, t_raycasting *rc, int x)
{
	int	y;
	int	tex_y;
	int tex_x;
	int	pixel_index;
	int	color;
	int screen_index;
	t_texture *current_texture;

	// Select texture based on wall side and direction
    if (rc->side == 0) // Vertical walls (North/South faces)
    {
        if (rc->step_x > 0)
            current_texture = game->ea_texture; // East wall (player looking west)
        else
            current_texture = game->we_texture; // West wall (player looking east)
    }
    else // Horizontal walls (East/West faces)
    {
        if (rc->step_y > 0)
            current_texture = game->so_texture; // South wall (player looking north)
        else
            current_texture = game->no_texture; // North wall (player looking south)
    }

    tex_x = (int)(rc->wall_x * current_texture->width);
	y = rc->draw_start;
	while(y < rc->draw_end)
	{
		tex_y = (int)(y - rc->draw_start) * current_texture->height / rc->line_height ;
		pixel_index = tex_y * current_texture->line_len + tex_x * (current_texture->bpp / 8);;
		color = *(unsigned int *)(current_texture->addr + pixel_index);
		screen_index = (y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
		*(unsigned int *)(game->mlx->img_data + screen_index) = color;
		y++;
	}
}

void raycasting(t_game *game)
{
	int		x;
	double camera_x;
	t_raycasting *rc;

	rc = game->raycast;
	rc->plane_x = -1 * game->player->dir_y;
	rc->plane_y = +1 * game->player->dir_x;

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
		printing_column(game, rc, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, game->mlx->img_ptr, 0, 0);
}