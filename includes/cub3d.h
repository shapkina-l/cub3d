/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:54:33 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/11 21:53:39 by lshapkin         ###   ########.fr       */
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

# define ESC_KEY	65307
# define W_KEY		119
# define A_KEY		97
# define S_KEY		115
# define D_KEY		100
# define LEFT_KEY	65361
# define RIGHT_KEY	65363

typedef struct s_player
{
	double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
    int     move_forward;
    int     move_backward;
    int     move_left;
    int     move_right;
    int     rotate_left;
    int     rotate_right;
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
	t_mlx		*mlx;
	t_map		*map;
	t_player	*player;
}	t_game;

int	init_graphics(t_game *game);
int	error_msg(char *message);
int	game_loop(t_game *game);
int	setup_events(t_game *game);
int	exit_game(t_game *game);

#endif