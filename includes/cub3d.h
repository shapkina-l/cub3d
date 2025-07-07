/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:54:33 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/07 15:16:41 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>

//replace int with proper type everywhere

typedef struct s_player
{
	int	position;
	int	direction;
	int	plane;
}	t_player;

typedef struct s_map
{
	int	grid;
	int	dimensions;
}	t_map;

typedef struct s_texture
{
	int	paths;
	int	images;
}	t_texture;

typedef struct s_game
{
	int	window;
	int	images;
	int	mlx;
}	t_game;

#endif