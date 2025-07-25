
#include "../includes/cub3d.h"

int	wall_check(double move_speed, t_game *game, int code)
{
	double	x;
	double	y;
	double radius = 0.2;

	if (code == 1)
	{
		x = (game->player->x + game->player->dir_x * move_speed);
		y = (game->player->y + game->player->dir_y * move_speed);
	}
	if (code == 2)
	{
		x = (game->player->x - game->player->dir_x * move_speed);
		y = (game->player->y - game->player->dir_y * move_speed);
	}
	if (code == 3)
	{
		x = (game->player->x - game->player->dir_y * move_speed);
		y = (game->player->y + game->player->dir_x * move_speed);
	}
	if (code == 4)
	{
		x = (game->player->x + game->player->dir_y * move_speed);
		y = (game->player->y - game->player->dir_x * move_speed);
	}
	int x_min = (int)(x - radius);
    int x_max = (int)(x + radius);
    int y_min = (int)(y - radius);
    int y_max = (int)(y + radius);

    for (int i = y_min; i <= y_max; i++)
    {
        for (int j = x_min; j <= x_max; j++)
        {
            if (game->map->map[i][j] == '1')
                return 0; // collision
        }
    }

    return 1; // no collision

	// if (code == 1)
	// {
	// 	x = (game->player->x + game->player->dir_x * move_speed) - 0.2;
	// 	y = (game->player->y + game->player->dir_y * move_speed) - 0.2;
	// }
	// if (code == 2)
	// {
	// 	x = (game->player->x - game->player->dir_x * move_speed) + 0.2;
	// 	y = (game->player->y - game->player->dir_y * move_speed) + 0.2;
	// }
	// if (code == 3)
	// {
	// 	x = (game->player->x - game->player->dir_y * move_speed) - 0.2;
	// 	y = (game->player->y + game->player->dir_x * move_speed) + 0.2;
	// }
	// if (code == 4)
	// {
	// 	x = (game->player->x + game->player->dir_y * move_speed) - 0.2;
	// 	y = (game->player->y - game->player->dir_x * move_speed) + 0.2;
	// }
	// return (game->map->map[(int)y][(int)x] != '1');
}

void	move_player(t_game *game, t_player *player)
{
	double	move_speed;

	move_speed = 0.02;
	if (player->move_forward == 1 && wall_check(move_speed, game, 1))
	{
		player->x += player->dir_x * move_speed;
		player->y += player->dir_y * move_speed;
	}
	if (player->move_backward == 1 && wall_check(move_speed, game, 2))
	{
		player->x -= player->dir_x * move_speed;
		player->y -= player->dir_y * move_speed;
	}
	if (player->move_right == 1 && wall_check(move_speed, game, 3))
	{
		player->x -= player->dir_y * move_speed;
		player->y += player->dir_x * move_speed;
	}
	if (player->move_left == 1 && wall_check(move_speed, game, 4))
	{
		player->x += player->dir_y * move_speed;
		player->y -= player->dir_x * move_speed;
	}
}

void	rotate_player(t_player *player, t_rc *rc)
{
	double	speed;
	double	old_dir_x;
	double	old_plane_x;

	speed = 0.05;
	if (player->rotate_right == 1)
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(speed) - player->dir_y * sin(speed);
		player->dir_y = old_dir_x * sin(speed) + player->dir_y * cos(speed);
		old_plane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * cos(speed) - rc->plane_y * sin(speed);
		rc->plane_y = old_plane_x * sin(speed) + rc->plane_y * cos(speed);
	}
	if (player->rotate_left == 1)
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-speed)
			- player->dir_y * sin(-speed);
		player->dir_y = old_dir_x * sin(-speed) + player->dir_y * cos(-speed);
		old_plane_x = rc->plane_x;
		rc->plane_x = rc->plane_x * cos(-speed) - rc->plane_y * sin(-speed);
		rc->plane_y = old_plane_x * sin(-speed) + rc->plane_y * cos(-speed);
	}
}

void	update_player(t_game *game)
{
	move_player(game, game->player);
	rotate_player(game->player, game->raycast);
}
