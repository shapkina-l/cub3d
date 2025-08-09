/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:20:03 by lshapkin          #+#    #+#             */
/*   Updated: 2025/08/04 13:20:31 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_textured_floor_helper(t_game *game, t_ceiling_print *f, int x)
{
	f->row_distance = (WIN_HEIGHT / 2.0) / (double)f->p_y;
	f->floor_step_x = f->row_distance
		* (f->ray_dir_x1 - f->ray_dir_x0) / WIN_WIDTH;
	f->floor_step_y = f->row_distance
		* (f->ray_dir_y1 - f->ray_dir_y0) / WIN_WIDTH;
	f->floor_x_left = game->player->x + f->row_distance * f->ray_dir_x0;
	f->floor_y_left = game->player->y + f->row_distance * f->ray_dir_y0;
	f->floor_x = f->floor_x_left + f->floor_step_x * x;
	f->floor_y = f->floor_y_left + f->floor_step_y * x;
	f->tex_scale = 1.0;
	f->tex_x = (int)(game->floor_texture->width
			* (f->floor_x * f->tex_scale - floor(f->floor_x * f->tex_scale)));
	f->tex_y = (int)(game->floor_texture->height
			* (f->floor_y * f->tex_scale - floor(f->floor_y * f->tex_scale)));
	while (f->tex_x < 0)
		f->tex_x += game->floor_texture->width;
	while (f->tex_y < 0)
		f->tex_y += game->floor_texture->height;
	f->tex_x %= game->floor_texture->width;
	f->tex_y %= game->floor_texture->height;
	if (f->tex_x >= game->floor_texture->width)
		f->tex_x = game->floor_texture->width - 1;
	if (f->tex_y >= game->floor_texture->height)
		f->tex_y = game->floor_texture->height - 1;
}

void	print_textured_floor(t_game *game, t_rc *rc, t_print *p, int x)
{
	t_ceiling_print	f;

	calculate_ray_dir(game, &f, rc);
	p->y = rc->draw_end + 1;
	while (p->y < WIN_HEIGHT)
	{
		f.p_y = p->y - WIN_HEIGHT / 2;
		if (f.p_y == 0)
		{
			p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
			*(unsigned int *)(game->mlx->img_data + p->screen_index) = 0x000000;
			p->y++;
			continue ;
		}
		print_textured_floor_helper(game, &f, x);
		f.pixel_index = f.tex_y * game->floor_texture->line_len
			+ f.tex_x * (game->floor_texture->bpp / 8);
		f.color = *(unsigned int *)(game->floor_texture->addr
				+ f.pixel_index);
		p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
		*(unsigned int *)(game->mlx->img_data + p->screen_index) = f.color;
		p->y++;
	}
}
