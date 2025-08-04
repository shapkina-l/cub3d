/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:57:59 by lshapkin          #+#    #+#             */
/*   Updated: 2025/08/04 12:46:00 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	error_msg(char *message)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (message)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	return (1);
}

int	exit_game(t_game *game)
{
	free_all(game);
	exit (0);
}

void	free_all(t_game	*game)
{
	if (game)
	{
		if (game->map)
			free_map(game);
		free_textures(game);
		if (game->player)
			free(game->player);
		if (game->raycast)
			free (game->raycast);
		if (game->minimap)
			free_minimap(game);
		if (game->z_buffer)
			free(game->z_buffer);
		if (game->mlx)
			free_mlx(game);
		free (game);
	}
}
