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

void	free_init(t_init *init)
{
	int	i;
	
	if (init->array)
	{
		i = -1;
		while (init->array[++i])
			free(init->array[i]);
		free(init->array);
	}
	if (init->test_map)
	{
		i = -1;
		while (init->test_map[++i])
			free(init->test_map[i]);
		free(init->test_map);
	}
}

void	free_map(t_game	*game)
{
	int	i;

	if (game->map->no_texture)
		free(game->map->no_texture);
	if (game->map->so_texture)
		free(game->map->so_texture);
	if (game->map->we_texture)
		free(game->map->we_texture);
	if (game->map->ea_texture)
		free(game->map->ea_texture);
	if (game->map->ceiling)
		free(game->map->ceiling);
	if (game->map->floor)
		free(game->map->floor);
	if (game->map->map)
	{
		i = -1;
		while (game->map->map[++i])
			free(game->map->map[i]);
		free(game->map->map);
	}
	free(game->map);
}

void	free_texture(t_game	*game, char type)
{
	t_texture	*ptr;

	ptr = NULL;
	if (type == 'N')
		ptr = game->no_texture;
	else if (type == 'S')
		ptr = game->so_texture;
	else if (type == 'W')
		ptr = game->we_texture;
	else if (type == 'E')
		ptr = game->ea_texture;
	if (ptr)
	{
		if (ptr->img)
			mlx_destroy_image(game->mlx->mlx_ptr, ptr->img);
		free(ptr);
	}
}

void	free_mlx(t_game	*game)
{
	if (game->mlx->img_ptr)
		mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->img_ptr);
	if (game->mlx->win_ptr)
		mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	if (game->mlx->mlx_ptr)
	{	
		mlx_destroy_display(game->mlx->mlx_ptr);
		free(game->mlx->mlx_ptr);
	}
	free (game->mlx);
}

void	free_all(t_game	*game)
{
	if (game)
	{
		if (game->map) 
			free_map(game);
		if (game->no_texture)
			free_texture(game, 'N');
		if (game->so_texture)
			free_texture(game, 'S');
		if (game->we_texture)
			free_texture(game, 'W');
		if (game->ea_texture)
			free_texture(game, 'E');
		if (game->player)
			free(game->player);
		if (game->raycast)
			free (game->raycast);
		if (game->mlx)
			free_mlx(game);
		free (game);
	}
}

int	exit_game(t_game *game)
{
	free_all(game);
	exit (0);
}
