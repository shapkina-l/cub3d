#include "../includes/cub3d.h"

int	create_test_border_row(t_init *data, int row)
{
	int	i;

	data->test_map[row] = malloc((data->width + 3) * sizeof(char));
	if (!data->test_map[row])
		return (0);
	i = 0;
	while (i < (data->width + 2))
	{
		data->test_map[row][i] = ' ';
		i++;
	}
	data->test_map[row][i] = '\0';
	return (1);
}

int	set_test_map_matrix(t_init *data, int start)
{
	int	i;

	data->test_map = ft_calloc(data->height + 3, sizeof(char *));
	if (!data->test_map)
		return (ft_printf("Error\n"), 0);
	if (!create_test_border_row(data, 0))
		return (ft_printf("Error\n"), 0);
	i = 1;
	while (i <= data->height)
	{
		data->test_map[i] = ft_strdup_spaces(data->array[start + i - 1],
				data->width);
		if (!data->test_map[i])
			return (ft_printf("Error\n"), 0);
		i++;
	}
	if (!create_test_border_row(data, data->height + 1))
		return (ft_printf("Error\n"), 0);
	data->test_map[data->height + 2] = NULL;
	return (1);
}


int	validate_map_boundaries(t_init *data)
{
	return (fill(data, 0, 0));
}

int	fill(t_init *data, int y, int x)
{
	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return (1);
	if (data->test_map[y][x] == '1' || data->test_map[y][x] == 'X')
		return (1);
	if (data->test_map[y][x] == '0' || data->test_map[y][x] == 'N'
		|| data->test_map[y][x] == 'S' || data->test_map[y][x] == 'W'
		|| data->test_map[y][x] == 'E')
		return (0);
	data->test_map[y][x] = 'X';
	if (!check_fill_neighbors(data, y, x))
		return (0);
	return (1);
}

int	check_fill_neighbors(t_init *data, int y, int x)
{
	if (!fill(data, y, x + 1))
		return (0);
	if (!fill(data, y, x - 1))
		return (0);
	if (!fill(data, y + 1, x))
		return (0);
	if (!fill(data, y - 1, x))
		return (0);
	if (!fill(data, y + 1, x + 1))
		return (0);
	if (!fill(data, y - 1, x - 1))
		return (0);
	if (!fill(data, y + 1, x - 1))
		return (0);
	if (!fill(data, y - 1, x + 1))
		return (0);
	return (1);
}
