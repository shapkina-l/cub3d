
#include "../../includes/cub3d.h"

void	render_object_sprite(t_game *game, t_object *obj)
{
	if (!obj->active)
		return ;

	// Transform object position to screen coordinates
	double sprite_x = obj->x - game->player->x;
	double sprite_y = obj->y - game->player->y;

	// Apply inverse camera transformation
	double inv_det = 1.0 / (game->raycast->plane_x * game->player->dir_y -
							game->player->dir_x * game->raycast->plane_y);

	double transform_x = inv_det * (game->player->dir_y * sprite_x -
									game->player->dir_x * sprite_y);
	double transform_y = inv_det * (-game->raycast->plane_y * sprite_x +
									game->raycast->plane_x * sprite_y);

	// Don't render if behind player
	if (transform_y <= 0)
		return ;

	// Calculate sprite screen position
	int sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));

	// Calculate sprite height and width with configurable scale
	int sprite_height = abs((int)(WIN_HEIGHT / transform_y * 0.3));
	int sprite_width = abs((int)(WIN_HEIGHT / transform_y * 0.3));

	// Calculate drawing bounds
	int draw_start_y = -sprite_height / 2 + WIN_HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	int draw_end_y = sprite_height / 2 + WIN_HEIGHT / 2;
	if (draw_end_y >= WIN_HEIGHT)
		draw_end_y = WIN_HEIGHT - 1;

	int draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	int draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WIN_WIDTH)
		draw_end_x = WIN_WIDTH - 1;

	// Use the single object texture
	t_texture *sprite_texture = game->object_texture;
	if (!sprite_texture)
		return;

	// Render sprite column by column
	int stripe;
	for (stripe = draw_start_x; stripe < draw_end_x; stripe++)
	{
		int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) *
						  sprite_texture->width / sprite_width) / 256;
		// Check if this pixel is closer than the wall (Z-buffer check)
		if (transform_y > 0 && stripe > 0 && stripe < WIN_WIDTH &&
			transform_y < game->z_buffer[stripe])
		{
			int y;
			for (y = draw_start_y; y < draw_end_y; y++)
			{
				int d = (y) * 256 - WIN_HEIGHT * 128 + sprite_height * 128;
				int tex_y = ((d * sprite_texture->height) / sprite_height) / 256;

				if (tex_y >= 0 && tex_y < sprite_texture->height)
				{
					int pixel_index = tex_y * sprite_texture->line_len +
									  tex_x * (sprite_texture->bpp / 8);
					unsigned int color = *(unsigned int *)(sprite_texture->addr + pixel_index);

					// Don't draw transparent pixels (assuming black is transparent)
					if ((color & 0x00FFFFFF) != 0)
					{
						int screen_index = (y * WIN_WIDTH + stripe) * (game->mlx->bpp / 8);
						*(unsigned int *)(game->mlx->img_data + screen_index) = color;
					}
				}
			}
		}
	}
}
