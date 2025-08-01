
#include "../../includes/cub3d.h"

typedef struct s_ceiling_print
{
	double			ray_dir_x0;
	double			ray_dir_y0;
	double			ray_dir_x1;
	double			ray_dir_y1;
	double			row_distance;
	double			floor_step_x;
	double			floor_step_y;
	double			floor_x_left;
	double			floor_y_left;
	double			floor_x;
	double			floor_y;
	int				tex_x;
	int				tex_y;
	int				pixel_index;
	unsigned int	color;
} t_ceiling_print;

void print_textured_ceiling(t_game *game, t_rc *rc, t_print *p, int x)
{
	t_ceiling_print c;

	// Calculate ray directions for leftmost and rightmost rays
	c.ray_dir_x0 = game->player->dir_x - rc->plane_x;
	c.ray_dir_y0 = game->player->dir_y - rc->plane_y;
	c.ray_dir_x1 = game->player->dir_x + rc->plane_x;
	c.ray_dir_y1 = game->player->dir_y + rc->plane_y;

	while (p->y < rc->draw_start)
	{
		// Current y position compared to the center of the screen (horizon)
		int p_y = WIN_HEIGHT / 2 - p->y;

		// Skip if we're at the horizon line to avoid division by zero
		if (p_y == 0)
		{
			p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
			*(unsigned int *)(game->mlx->img_data + p->screen_index) = 0x000000; // Black line at horizon
			p->y++;
			continue;
		}

		// Horizontal distance from the camera to the ceiling for the current row
		// For ceiling, we use the distance to the upper plane
		c.row_distance = (WIN_HEIGHT / 2.0) / (double)p_y;

		// Calculate the real world step vector we have to add for each x (parallel to camera plane)
		c.floor_step_x = c.row_distance * (c.ray_dir_x1 - c.ray_dir_x0) / WIN_WIDTH;
		c.floor_step_y = c.row_distance * (c.ray_dir_y1 - c.ray_dir_y0) / WIN_WIDTH;

		// Real world coordinates of the leftmost column for this row
		c.floor_x_left = game->player->x + c.row_distance * c.ray_dir_x0;
		c.floor_y_left = game->player->y + c.row_distance * c.ray_dir_y0;

		// Real world coordinates for this specific column and row
		c.floor_x = c.floor_x_left + c.floor_step_x * x;
		c.floor_y = c.floor_y_left + c.floor_step_y * x;

		// Get texture coordinates (with proper wrapping)
		// Scale the texture coordinates to make the texture appear at reasonable size
		double tex_scale = 1.0; // Adjust this value to scale texture size (1.0 = normal, 2.0 = half size, 0.5 = double size)

		c.tex_x = (int)(game->ceiling_texture->width * (c.floor_x * tex_scale - floor(c.floor_x * tex_scale)));
		c.tex_y = (int)(game->ceiling_texture->height * (c.floor_y * tex_scale - floor(c.floor_y * tex_scale)));

		// Ensure texture coordinates are within bounds (handle negative values)
		while (c.tex_x < 0)
			c.tex_x += game->ceiling_texture->width;
		while (c.tex_y < 0)
			c.tex_y += game->ceiling_texture->height;
		c.tex_x %= game->ceiling_texture->width;
		c.tex_y %= game->ceiling_texture->height;

		// Ensure we don't go out of bounds
		if (c.tex_x >= game->ceiling_texture->width)
			c.tex_x = game->ceiling_texture->width - 1;
		if (c.tex_y >= game->ceiling_texture->height)
			c.tex_y = game->ceiling_texture->height - 1;

		// Get color from texture
		c.pixel_index = c.tex_y * game->ceiling_texture->line_len + c.tex_x * (game->ceiling_texture->bpp / 8);
		c.color = *(unsigned int *)(game->ceiling_texture->addr + c.pixel_index);

		// Put pixel to screen
		p->screen_index = (p->y * WIN_WIDTH + x) * (game->mlx->bpp / 8);
		*(unsigned int *)(game->mlx->img_data + p->screen_index) = c.color;

		p->y++;
	}
}
