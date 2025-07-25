/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:57:32 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/25 20:02:05 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_position(int code, double move_speed, t_game *game,
			t_wall_check *check)
{
	if (code == 1)
	{
		check->x = (game->player->x + game->player->dir_x * move_speed);
		check->y = (game->player->y + game->player->dir_y * move_speed);
	}
	if (code == 2)
	{
		check->x = (game->player->x - game->player->dir_x * move_speed);
		check->y = (game->player->y - game->player->dir_y * move_speed);
	}
	if (code == 3)
	{
		check->x = (game->player->x - game->player->dir_y * move_speed);
		check->y = (game->player->y + game->player->dir_x * move_speed);
	}
	if (code == 4)
	{
		check->x = (game->player->x + game->player->dir_y * move_speed);
		check->y = (game->player->y - game->player->dir_x * move_speed);
	}
}

int	wall_check(double move_speed, t_game *game, int code)
{
	t_wall_check	check;
	int				i;
	int				j;

	set_position(code, move_speed, game, &check);
	check.radius = 0.2;
	check.x_min = (int)(check.x - check.radius);
	check.x_max = (int)(check.x + check.radius);
	check.y_min = (int)(check.y - check.radius);
	check.y_max = (int)(check.y + check.radius);
	i = check.y_min;
	while (i <= check.y_max)
	{
		j = check.x_min;
		while (j <= check.x_max)
		{
			if (game->map->map[i][j] == '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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
