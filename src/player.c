
#include "../includes/cub3d.h"

int	wall_check(double move_speed, t_game *game, int code)
{
	double x;
	double y;

	if (code == 1)
	{
		x = game->player->x + game->player->dir_x * move_speed;
		y = game->player->y + game->player->dir_y * move_speed;
	}
	if (code == 2)
	{
		x = game->player->x - game->player->dir_x * move_speed;
		y = game->player->y - game->player->dir_y * move_speed;
	}
	if (code == 3)
	{
		x = game->player->x - game->player->dir_y * move_speed;
		y = game->player->y + game->player->dir_x * move_speed;
	}
	if (code == 4)
	{
		x = game->player->x + game->player->dir_y * move_speed;
		y = game->player->y - game->player->dir_x * move_speed;
	}
	return (game->map->map[(int)y][(int)x] != '1');
}

void    move_player(t_game *game)
{
    double move_speed;

    move_speed = 0.1;
    if (game->player->move_forward == 1 && wall_check(move_speed, game, 1))
	{
		game->player->x += game->player->dir_x * move_speed;
		game->player->y += game->player->dir_y * move_speed;
	}
	if (game->player->move_backward == 1 && wall_check(move_speed, game, 2))
	{
		game->player->x -= game->player->dir_x * move_speed;
		game->player->y -= game->player->dir_y * move_speed;
	}
	if (game->player->move_right == 1 && wall_check(move_speed, game, 3))
	{
		game->player->x -= game->player->dir_y * move_speed;
		game->player->y += game->player->dir_x * move_speed;
	}
	if (game->player->move_left == 1 && wall_check(move_speed, game, 4))
	{
		game->player->x += game->player->dir_y * move_speed;
		game->player->y -= game->player->dir_x * move_speed;
	}
}

void    rotate_player(t_game *game)
{
    double rot_speed;
    double old_dir_x;
    double old_plane_x;

	rot_speed = 0.05;
    if (game->player->rotate_right == 1)
	{
		old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(rot_speed) - game->player->dir_y * sin(rot_speed);
		game->player->dir_y = old_dir_x * sin(rot_speed) + game->player->dir_y * cos(rot_speed);
	
		old_plane_x = game->raycast->plane_x;
		game->raycast->plane_x = game->raycast->plane_x * cos(rot_speed) - game->raycast->plane_y * sin(rot_speed);
		game->raycast->plane_y = old_plane_x * sin(rot_speed) + game->raycast->plane_y * cos(rot_speed);
	}
	if (game->player->rotate_left == 1)
	{
		old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-rot_speed) - game->player->dir_y * sin(-rot_speed);
		game->player->dir_y = old_dir_x * sin(-rot_speed) + game->player->dir_y * cos(-rot_speed);

		old_plane_x = game->raycast->plane_x;
		game->raycast->plane_x = game->raycast->plane_x * cos(-rot_speed) - game->raycast->plane_y * sin(-rot_speed);
		game->raycast->plane_y = old_plane_x * sin(-rot_speed) + game->raycast->plane_y * cos(-rot_speed);
	}
}

void update_player(t_game *game)
{
	move_player(game);
	rotate_player(game);
}