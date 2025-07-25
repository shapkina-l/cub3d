/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:56:50 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/25 20:01:23 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_game_extra(t_game *game, char *argument)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (0);
	ft_memset(game->map, 0, sizeof(t_map));
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (0);
	ft_memset(game->player, 0, sizeof(t_player));
	if (!file_validation(game, argument))
		return (0);
	game->raycast = malloc(sizeof(t_rc));
	if (!game->raycast)
		return (1);
	ft_memset(game->raycast, 0, sizeof(t_rc));
	return (1);
}

int	init_game(t_game	*game, char *argument)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		return (1);
	ft_memset(game->mlx, 0, sizeof(t_mlx));
	init_game_extra(game, argument);
	game->no_texture = malloc(sizeof(t_texture));
	if (!game->no_texture)
		return (1);
	ft_memset(game->no_texture, 0, sizeof(t_texture));
	game->so_texture = malloc(sizeof(t_texture));
	if (!game->so_texture)
		return (1);
	ft_memset(game->so_texture, 0, sizeof(t_texture));
	game->ea_texture = malloc(sizeof(t_texture));
	if (!game->ea_texture)
		return (1);
	ft_memset(game->ea_texture, 0, sizeof(t_texture));
	game->we_texture = malloc(sizeof(t_texture));
	if (!game->we_texture)
		return (1);
	ft_memset(game->we_texture, 0, sizeof(t_texture));
	return (0);
}

int	game_loop(t_game *game)
{
	update_player(game);
	raycasting(game);
	return (0);
}

int	main(int arc, char **arv)
{
	t_game	*game;

	if (!argument_validation(arc, arv))
		return (1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (error_msg("Memory allocation failed."), 1);
	ft_memset(game, 0, sizeof(t_game));
	if (init_game(game, arv[1]))
		return (error_msg("Data initialization failed."),
			exit_game(game), 1);
	if (init_graphics(game))
		return (error_msg("Graphics initialization failed."),
			exit_game(game), 1);
	setup_events(game);
	mlx_loop(game->mlx->mlx_ptr);
	exit_game(game);
	return (0);
}
