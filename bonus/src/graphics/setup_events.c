/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:48:51 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/26 14:16:19 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		exit_game(game);
	else if (keycode == W_KEY)
		game->player->move_forward = 1;
	else if (keycode == S_KEY)
		game->player->move_backward = 1;
	else if (keycode == A_KEY)
		game->player->move_left = 1;
	else if (keycode == D_KEY)
		game->player->move_right = 1;
	else if (keycode == LEFT_KEY)
		game->player->rotate_left = 1;
	else if (keycode == RIGHT_KEY)
		game->player->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		exit_game(game);
	else if (keycode == W_KEY)
		game->player->move_forward = 0;
	else if (keycode == S_KEY)
		game->player->move_backward = 0;
	else if (keycode == A_KEY)
		game->player->move_left = 0;
	else if (keycode == D_KEY)
		game->player->move_right = 0;
	else if (keycode == LEFT_KEY)
		game->player->rotate_left = 0;
	else if (keycode == RIGHT_KEY)
		game->player->rotate_right = 0;
	return (0);
}

int	setup_events(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, 2, (1L << 0), key_press, game);
	mlx_hook(game->mlx->win_ptr, 3, (1L << 1), key_release, game);
	mlx_hook(game->mlx->win_ptr, 17, (1L << 17), exit_game, game);
	mlx_loop_hook(game->mlx->mlx_ptr, game_loop, game);
	return (0);
}
