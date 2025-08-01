
#include "../../includes/cub3d.h"

int	render_object_step_one(t_game *game, t_object *obj, t_book_rendering *b)
{
	b->sprite_x = obj->x - game->player->x;
	b->sprite_y = obj->y - game->player->y;
	b->inv_det = 1.0 / (game->raycast->plane_x * game->player->dir_y
			- game->player->dir_x * game->raycast->plane_y);
	b->transform_x = b->inv_det * (game->player->dir_y * b->sprite_x
			- game->player->dir_x * b->sprite_y);
	b->transform_y = b->inv_det * (-game->raycast->plane_y * b->sprite_x
			+ game->raycast->plane_x * b->sprite_y);
	if (b->transform_y <= 0)
		return (1);
	b->sp_screen_x = (int)((WIN_WIDTH / 2)
			* (1 + b->transform_x / b->transform_y));
	b->sprite_height = abs((int)(WIN_HEIGHT / b->transform_y * 0.3));
	b->sprite_width = abs((int)(WIN_HEIGHT / b->transform_y * 0.3));
	return (0);
}

void	render_object_step_two(t_book_rendering *b)
{
	b->draw_start_y = WIN_HEIGHT / 2 + ((float)b->sprite_height);
	if (b->draw_start_y < 0)
		b->draw_start_y = 0;
	b->draw_end_y = WIN_HEIGHT / 2 + b->sprite_height
		+ ((float)b->sprite_height);
	if (b->draw_end_y >= WIN_HEIGHT)
		b->draw_end_y = WIN_HEIGHT - 1;
	b->draw_start_x = -b->sprite_width / 2 + b->sp_screen_x;
	if (b->draw_start_x < 0)
		b->draw_start_x = 0;
	b->draw_end_x = b->sprite_width / 2 + b->sp_screen_x;
	if (b->draw_end_x >= WIN_WIDTH)
		b->draw_end_x = WIN_WIDTH - 1;
}

void	render_object_stripe(int stripe, t_texture *texture,
								t_game *game, t_book_rendering *b)
{
	b->tex_x = (int)(256 * (stripe - (-b->sprite_width / 2 + b->sp_screen_x))
			* texture->width / b->sprite_width) / 256;
	if (b->transform_y > 0 && stripe > 0 && stripe < WIN_WIDTH
		&& b->transform_y < game->z_buffer[stripe])
	{
		b->y = b->draw_start_y;
		while (b->y < b->draw_end_y)
		{
			b->d = (b->y - b->draw_start_y) * 256;
			b->tex_y = (b->d * texture->height) / (b->sprite_height * 256);
			if (b->tex_y >= 0 && b->tex_y < texture->height)
			{
				b->pixel_index = b->tex_y * texture->line_len
					+ b->tex_x * (texture->bpp / 8);
				b->color = *(unsigned int *)(texture->addr + b->pixel_index);
				if ((b->color & 0x00FFFFFF) != 0)
				{
					b->s_i = (b->y * WIN_WIDTH + stripe) * (game->mlx->bpp / 8);
					*(unsigned int *)(game->mlx->img_data + b->s_i) = b->color;
				}
			}
			b->y++;
		}
	}
}

void	render_object_sprite(t_game *game, t_object *obj)
{
	t_book_rendering	b;
	t_texture			*sprite_texture;
	int					stripe;

	if (!obj->active)
		return ;
	if (render_object_step_one(game, obj, &b))
		return ;
	render_object_step_two(&b);
	sprite_texture = game->object_texture;
	if (!sprite_texture)
		return ;
	stripe = b.draw_start_x;
	while (stripe < b.draw_end_x)
	{
		render_object_stripe(stripe, sprite_texture, game, &b);
		stripe++;
	}
}
