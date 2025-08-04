
#include "../../includes/cub3d.h"

// Function to render score text on the window
void	render_score(t_game *game)
{
	char	*score_text;
	char	*score_num;
	char	*temp;
	int		text_width;
	int		x_pos;

	score_num = ft_itoa(game->score);
	if (!score_num)
		return ;
	temp = ft_strjoin("Score: ", score_num);
	if (!temp)
	{
		free(score_num);
		return ;
	}
	score_text = temp;
	text_width = ft_strlen(score_text) * 6;
	x_pos = WIN_WIDTH - text_width - 10;
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
		x_pos, WIN_HEIGHT - 20, 0xFFFFFF, score_text);
	free(score_num);
	free(score_text);
}




