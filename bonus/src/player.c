/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:57:32 by lshapkin          #+#    #+#             */
/*   Updated: 2025/08/04 12:08:54 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	wall_check(t_game *game, t_vec2d move_vec)
{
	t_wall_check	check;
	int				i;
	int				j;

	check.x = game->player->x + move_vec.x;
	check.y = game->player->y + move_vec.y;
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

void	try_slide(t_game *game, t_player *player, t_vec2d move)
{
	t_vec2d	move_x;
	t_vec2d	move_y;
	int		x_clear;
	int		y_clear;

	move_x.x = move.x;
	move_x.y = 0;
	move_y.x = 0;
	move_y.y = move.y;
	x_clear = wall_check(game, move_x);
	y_clear = wall_check(game, move_y);
	if (x_clear)
		player->x += move.x;
	if (y_clear)
		player->y += move.y;
}

void	move_player(t_game *game, t_player *player,
		t_vec2d move, double move_speed)
{
	if (player->move_forward)
	{
		move.x = player->dir_x * move_speed;
		move.y = player->dir_y * move_speed;
		try_slide(game, player, move);
	}
	if (player->move_backward)
	{
		move.x = -player->dir_x * move_speed;
		move.y = -player->dir_y * move_speed;
		try_slide(game, player, move);
	}
	if (player->move_right)
	{
		move.x = -player->dir_y * move_speed;
		move.y = player->dir_x * move_speed;
		try_slide(game, player, move);
	}
	if (player->move_left)
	{
		move.x = player->dir_y * move_speed;
		move.y = -player->dir_x * move_speed;
		try_slide(game, player, move);
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
	t_vec2d	move;
	double	move_speed;

	move.x = 0;
	move.y = 0;
	move_speed = 0.06;
	move_player(game, game->player, move, move_speed);
	rotate_player(game->player, game->raycast);
}
