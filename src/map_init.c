/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:57:18 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/25 16:57:19 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	set_map_matrix(t_init *data, t_map *map, int start)
{
	int	i;

	i = 0;
	while (data->array[start + i])
		i++;
	map->map = ft_calloc(i + 2, sizeof(char *));
	if (!map->map)
		return (0);
	i = 0;
	while (data->array[start + i])
	{
		map->map[i] = ft_strdup(data->array[start + i]);
		if (!map->map[i])
		{
			map->map[i] = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

void	set_paths(t_map *map, const char *str)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return ;
	start = i;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	end = i;
	if (!ft_strncmp("NO", &str[start], end - start))
		set_texture_path(map, str, 'N');
	else if (!ft_strncmp("SO", &str[start], end - start))
		set_texture_path(map, str, 'S');
	else if (!ft_strncmp("WE", &str[start], end - start))
		set_texture_path(map, str, 'W');
	else if (!ft_strncmp("EA", &str[start], end - start))
		set_texture_path(map, str, 'E');
	else if (!ft_strncmp("F", &str[start], end - start))
		set_colour_path(map, str, 'F');
	else if (!ft_strncmp("C", &str[start], end - start))
		set_colour_path(map, str, 'C');
}

int	create_map_and_test_map(t_init *data, t_map *map, int j)
{
	int		i;
	char	c;

	i = 0;
	while (data->array[j][i] == ' ')
		i++;
	c = data->array[j][i];
	if (c == '1' || c == '0')
	{
		if (!set_map_matrix(data, map, j))
			return (0);
		find_map_dimensions(data, map);
		if (!set_test_map_matrix(data, j))
			return (0);
		return (1);
	}
	return (2);
}

int	verify_rgb_within_bounds(t_map *map)
{
	if (map->floor->r < 0 || map->floor->r > 255
		|| map->floor->g < 0 || map->floor->g > 255
		|| map->floor->b < 0 || map->floor->b > 255)
		return (0);
	if (map->ceiling->r < 0 || map->ceiling->r > 255
		|| map->ceiling->g < 0 || map->ceiling->g > 255
		|| map->ceiling->b < 0 || map->ceiling->b > 255)
		return (0);
	return (1);
}

int	set_map_data(t_init *data, t_map *map)
{
	int	j;
	int	result;

	j = 0;
	while (data->array[j])
	{
		if (data->array[j][0] == '\0')
		{
			j++;
			continue ;
		}
		set_paths(map, data->array[j]);
		if (!verify_rgb_within_bounds(map))
			return (0);
		result = create_map_and_test_map(data, map, j);
		if (result == 0)
			return (0);
		else if (result == 1)
			return (1);
		j++;
	}
	return (0);
}
