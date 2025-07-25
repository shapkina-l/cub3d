
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
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
# define WIN_WIDTH	1200
# define WIN_HEIGHT	900

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	// double	plane_x;
	// double	plane_y;
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
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

typedef struct s_raycasting
{
	int		map_x;
	int		map_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double 	delta_dist_x;
	double 	delta_dist_y;
	double 	plane_x;
	double 	plane_y;
	int		step_x;
	int 	step_y;
	double 	side_dist_x;
	double 	side_dist_y;
	int		side;
	double	wall_dist;
	int 	line_height;
	int 	draw_start;
	int 	draw_end;
	double 	wall_x;
}	t_raycasting;

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
	char	**map;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_game
{
	t_mlx			*mlx;
	t_map			*map;
	t_texture		*no_texture;
	t_texture		*so_texture;
	t_texture		*we_texture;
	t_texture		*ea_texture;
	t_player		*player;
	t_raycasting	*raycast;
}	t_game;

typedef struct s_init
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	int		width;
	int		height;
	char	**array;
	char	**test_map;
}	t_init;

// Array Creation
int		count_lines(char *cub_address);
int		build_array_helper(t_init *data, char *line, int fd);
int		build_array_from_file(t_init *data, char *cub_address);
// Validation Data Initialization
void	find_map_dimensions(t_init *data, t_map *map);
void	initialize_init(t_init *data);
void	initialize_map(t_map *map);
// File Validation
int		validate_map_chars(t_map *map);
int		handle_id_match(t_init *data, const char *str, int start, int end);
int		first_word_analysis(t_init *data, const char *str);
int		validate_cub_elements(t_init *data);
int		validate_file_format(char *str);
// Map Initialization
int		set_map_matrix(t_init *data, t_map *map, int start);
void	set_paths(t_map *map, const char *str);
int		create_map_and_test_map(t_init *data, t_map *map, int j);
int		set_map_data(t_init *data, t_map *map);
// Test Matrix
int		create_test_border_row(t_init *data, int row);
int		set_test_map_matrix(t_init *data, int start);
int		validate_map_boundaries(t_init *data);
int		fill(t_init *data, int y, int x);
int		check_fill_neighbors(t_init *data, int y, int x);
// Validation Utils
int		ft_strlen_newline(const char *str);
char	*ft_strdup_newline(char *src);
char	*ft_strdup_spaces(const char *s, int width);
void	set_colour_path(t_map *map, const char *str, char type);
int		set_texture_path(t_map *map, const char *str, char type);
// Validation Utils 2
int		colour_verification(const char *str);
// Player-Character Placement
void	set_starting_point(t_map *map, t_player *player, int y, int x);
void	find_starting_point(t_map *map, t_player *player);
// Minilibx Handling
int		init_graphics(t_game *game);
int		error_msg(char *message);
int		game_loop(t_game *game);
int		setup_events(t_game *game);
int		exit_game(t_game *game);
int		load_textures(t_game *game);
int		validate_textures(t_game *game);
// Raycasting
void	raycasting(t_game *game);
// Main
void	free_init(t_init *init);
int		argument_validation(int arc, char **arv);
int		file_validation(t_game	*game, char *argument);
// Temporary
void	test_all_textures(t_game *game);

#endif
