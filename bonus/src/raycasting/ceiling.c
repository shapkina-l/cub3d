
#include "../../includes/cub3d.h"

void	calculate_ray_dir(t_game *game, t_ceiling_print *c, t_rc *rc)
{
	c->ray_dir_x0 = game->player->dir_x - rc->plane_x;
	c->ray_dir_y0 = game->player->dir_y - rc->plane_y;
	c->ray_dir_x1 = game->player->dir_x + rc->plane_x;
	c->ray_dir_y1 = game->player->dir_y + rc->plane_y;
}

void	print_textured_ceiling_helper(t_game *game, t_ceiling_print *c, int x)
{
	c->row_distance = (WIN_HEIGHT / 2.0) / (double)c->p_y;
	c->floor_step_x = c->row_distance
		* (c->ray_dir_x1 - c->ray_dir_x0) / WIN_WIDTH;
	c->floor_step_y = c->row_distance
		* (c->ray_dir_y1 - c->ray_dir_y0) / WIN_WIDTH;
	c->floor_x_left = game->player->x + c->row_distance * c->ray_dir_x0;
	c->floor_y_left = game->player->y + c->row_distance * c->ray_dir_y0;
	c->floor_x = c->floor_x_left + c->floor_step_x * x;
	c->floor_y = c->floor_y_left + c->floor_step_y * x;
	c->tex_scale = 1.0;
	c->tex_x = (int)(game->ceiling_texture->width
			* (c->floor_x * c->tex_scale - floor(c->floor_x * c->tex_scale)));
	c->tex_y = (int)(game->ceiling_texture->height
			* (c->floor_y * c->tex_scale - floor(c->floor_y * c->tex_scale)));
	while (c->tex_x < 0)
		c->tex_x += game->ceiling_texture->width;
	while (c->tex_y < 0)
		c->tex_y += game->ceiling_texture->height;
	c->tex_x %= game->ceiling_texture->width;
	c->tex_y %= game->ceiling_texture->height;
	if (c->tex_x >= game->ceiling_texture->width)
		c->tex_x = game->ceiling_texture->width - 1;
	if (c->tex_y >= game->ceiling_texture->height)
		c->tex_y = game->ceiling_texture->height - 1;
}

void	print_textured_ceiling(t_game *game, t_rc *rc, t_print *p, int x)
{
	t_ceiling_print	c;

	calculate_ray_dir(game, &c, rc);
	while (p->y < rc->draw_start)
	{
		c.p_y = WIN_HEIGHT / 2 - p->y;
		if (c.p_y == 0)
		{
			p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
			*(unsigned int *)(game->mlx->img_data + p->screen_index) = 0x000000;
			p->y++;
			continue ;
		}
		print_textured_ceiling_helper(game, &c, x);
		c.pixel_index = c.tex_y * game->ceiling_texture->line_len
			+ c.tex_x * (game->ceiling_texture->bpp / 8);
		c.color = *(unsigned int *)(game->ceiling_texture->addr
				+ c.pixel_index);
		p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
		*(unsigned int *)(game->mlx->img_data + p->screen_index) = c.color;
		p->y++;
	}
}
