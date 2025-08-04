/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:50:11 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/26 14:20:13 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgb_transformation(int r, int g, int b)
{
	return (((r & 0xFF) << 16)
		| ((g & 0xFF) << 8)
		| (b & 0xFF));
}

void	print_ceiling(t_game *game, t_rc *rc, t_print *p, int x)
{
	while (p->y < rc->draw_start)
	{
		p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
		*(unsigned int *)(game->mlx->img_data + p->screen_index) = p->ceiling_c;
		p->y++;
	}
}

void	printing_column_helper(t_game *game, t_rc *rc, t_print *p, int x)
{
	print_ceiling(game, rc, p, x);
	p->tex_x = (int)(rc->wall_x * p->cur_t->width);
	if (rc->side == 1 && rc->step_y > 0)
		p->tex_x = p->cur_t->width - p->tex_x - 1;
	while (p->y < rc->draw_end)
	{
		p->tex_y = (int)(p->y - (-rc->line_height / 2 + WIN_HEIGHT / 2))
			* p->cur_t->height / rc->line_height;
		if (p->tex_y >= p->cur_t->height)
			p->tex_y = p->cur_t->height - 1;
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
