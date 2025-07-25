#include "../../includes/cub3d.h"

void	wall_height(t_game *game, t_rc *rc)
{
	if (rc->side == 0)
		rc->wall_dist = (rc->map_x - game->player->x + (1 - rc->step_x) / 2)
			/ rc->ray_dir_x;
	else
		rc->wall_dist = (rc->map_y - game->player->y + (1 - rc->step_y) / 2)
			/ rc->ray_dir_y;
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

void	dda(t_game *game, t_rc *rc)
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
			break ;
	}
}

void	step_calculation(t_game *game, t_rc *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player->x - rc->map_x)
			* rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player->x)
			* rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player->y - rc->map_y)
			* rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - game->player->y)
			* rc->delta_dist_y;
	}
}

int	rgb_transformation(int r, int g, int b)
{
	return (((r & 0xFF) << 16)
		| ((g & 0xFF) << 8)
		| (b & 0xFF));
}

void	printing_column_helper(t_game *game, t_rc *rc, t_print *p, int x)
{
	while (p->y < rc->draw_start)
	{
		p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
		*(unsigned int *)(game->mlx->img_data + p->screen_index) = p->ceiling_c;
		p->y++;
	}
	p->tex_x = (int)(rc->wall_x * p->cur_t->width);
	while (p->y < rc->draw_end)
	{
		p->tex_y = (int)(p->y - rc->draw_start)
			* p->cur_t->height / rc->line_height ;
		p->pixel_index = p->tex_y * p->cur_t->line_len + p->tex_x
			* (p->cur_t->bpp / 8);
		p->color = *(unsigned int *)(p->cur_t->addr + p->pixel_index);
		p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
		*(unsigned int *)(game->mlx->img_data + p->screen_index) = p->color;
		p->y++;
	}
	while (p->y < WIN_HEIGHT)
	{
		p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
		*(unsigned int *)(game->mlx->img_data + p->screen_index) = p->floor_c;
		p->y++;
	}
}

void	initialize_print_struct(t_print *print)
{
	print->y = 0;
	print->tex_y = 0;
	print->tex_x = 0;
	print->pixel_index = 0;
	print->color = 0;
	print->floor_c = 0;
	print->ceiling_c = 0;
	print->screen_index = 0;
	print->cur_t = NULL;
}

void	printing_column(t_game *game, t_rc *rc, int x)
{
	t_print		print;

	initialize_print_struct(&print);
	if (rc->side == 0)
	{
		if (rc->step_x > 0)
			print.cur_t = game->ea_texture;
		else
			print.cur_t = game->we_texture;
	}
	else
	{
		if (rc->step_y > 0)
			print.cur_t = game->so_texture;
		else
			print.cur_t = game->no_texture;
	}
	print.ceiling_c = rgb_transformation(game->map->ceiling->r, 
			game->map->ceiling->g, game->map->ceiling->b);
	print.floor_c = rgb_transformation(game->map->floor->r, 
			game->map->floor->g, game->map->floor->b);
	print.y = 0;
	printing_column_helper(game, rc, &print, x);
}

void	raycasting(t_game *game)
{
	int		x;
	double	camera_x;
	t_rc	*rc;

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
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->mlx->img_ptr, 0, 0);
}
