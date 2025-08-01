
#include "../../includes/cub3d.h"

int	count_remaining_objects(t_game *game)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < game->object_count)
	{
		if (game->objects[i].active)
			count++;
		i++;
	}
	return (count);
}

int	all_objects_collected(t_game *game)
{
	return (count_remaining_objects(game) == 0);
}

void	render_final_score(t_game *game, int center_x, int center_y)
{
	char	*final_score;
	char	*score_text;
	char	*temp;

	final_score = ft_itoa(game->score);
	if (final_score)
	{
		temp = ft_strjoin("Final Score: ", final_score);
		if (temp)
		{
			score_text = temp;
			mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
				center_x - 30, center_y, 0xFFFFFF, score_text);
			free(score_text);
		}
		free(final_score);
	}
}

// Function to render the congratulations screen
void	render_congrats_screen(t_game *game)
{
	int		center_x;
	int		center_y;

	mlx_clear_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
		center_x - 30, center_y - 60, 0xFFFFFF, "CONGRATULATIONS!");
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
		center_x - 30, center_y - 30, 0xFFFFFF, "All books collected!");
	render_final_score(game, center_x, center_y);
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
		center_x - 30, center_y + 30, 0xFFFFFF, "Press ESC to exit");
}
