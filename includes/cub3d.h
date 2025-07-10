/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:54:33 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/10 13:16:33 by lshapkin         ###   ########.fr       */
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
}	t_player;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		line_len;
	int		endian;
	int		win_width;
	int		win_height;
}	t_mlx;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_color	*floor;
	t_color	*ceiling;
	int		**map;
}	t_map;

typedef struct s_texture
{
	char	*paths;
}	t_texture;

typedef struct s_game
{
	t_mlx	*mlx;
	t_map	*map;
}	t_game;

int	init_graphics(t_game *game);

#endif