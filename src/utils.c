/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:10:39 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/11 21:52:38 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int error_msg(char *message)
{
    write(STDERR_FILENO, "Error\n", 6);
    if (message)
    {
        write(STDERR_FILENO, message, ft_strlen(message));
        write(STDERR_FILENO, "\n", 1);
    }
    return (1);
}

int exit_game(t_game *game)
{
	if (game->mlx->img_ptr)
		mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->img_ptr);
	if (game->mlx->win_ptr)
		mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	if (game->mlx->mlx_ptr)
		mlx_destroy_display(game->mlx->mlx_ptr);
	free(game->mlx->mlx_ptr);
	exit (0); //free everything else?
}