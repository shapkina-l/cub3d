#include "../includes/cub3d.h"

int	validate_map_chars(t_map *map)
{
	int		i;
	int		j;
	int		count;
	char	c;

	count = 0;
	j = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			c = map->map[j][i];
			if (!(c == '0' || c == '1' || c == 'N' || c == 'E'
					|| c == 'S' || c == 'W' || c == ' ' || c == '\n'))
				return (0);
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
				count++;
			i++;
		}
		j++;
	}
	if (count > 1)
		return (0);
	return (1);
}

int	handle_id_match(t_init *data, const char *str, int start, int end)
{
	if (!ft_strncmp("NO", &str[start], end - start))
		data->no++;
	else if (!ft_strncmp("SO", &str[start], end - start))
		data->so++;
	else if (!ft_strncmp("WE", &str[start], end - start))
		data->we++;
	else if (!ft_strncmp("EA", &str[start], end - start))
		data->ea++;
	else if (!ft_strncmp("F", &str[start], end - start))
		data->f++;
	else if (!ft_strncmp("C", &str[start], end - start))
		data->c++;
	else if (!ft_strncmp("1", &str[start], 1))
		return (1);
	else
		return (0);
	return (1);
}

int	first_word_analysis(t_init *data, const char *str)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	start = i;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	end = i;
	return (handle_id_match(data, str, start, end));
}

int	validate_cub_elements(t_init *data)
{
	int	i;

	i = 0;
	while (data->array[i])
	{
		first_word_analysis(data, data->array[i]);
		i++;
	}
	if (data->no != 1 || data->so != 1 || data->we != 1
		|| data->ea != 1 || data->f != 1 || data->c != 1)
		return (0);
	return (1);
}

int	validate_file_format(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (1);
	if (ft_strncmp(&str[len - 4], ".cub", 4) != 0)
		return (0);
	return (1);
}
