#include "../../includes/cub3d.h"

int	ft_strlen_newline(const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] && str[i] != '\n')
			i++;
		return (i);
	}
	return (0);
}

char	*ft_strdup_newline(char *src)
{
	char	*dup;
	int		i;

	dup = malloc(ft_strlen_newline(src) + 1);
	if (!dup)
		return (0);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup_spaces(const char *s, int width)
{
	char	*res;
	int		i;

	res = malloc((width + 3) * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = ' ';
	i = 0;
	while (s[i])
	{
		res[i + 1] = s[i];
		i++;
	}
	while (i + 1 < width + 2)
	{
		res[i + 1] = ' ';
		i++;
	}
	res[i + 1] = '\0';
	return (res);
}

void	set_colour_path(t_map *map, const char *str, char type)
{
	int		i;
	t_color	*target;

	if (type == 'F')
		target = map->floor;
	else if (type == 'C')
		target = map->ceiling;
	else
		return ;
	i = 0;
	while (!ft_isdigit(str[i]))
		i++;
	target->r = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]))
		i++;
	target->g = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]))
		i++;
	target->b = ft_atoi(&str[i]);
}

int	set_texture_path(t_map *map, const char *str, char type)
{
	int			i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	if (type == 'N')
		map->no_texture = ft_strdup(&str[i]);
	else if (type == 'S')
		map->so_texture = ft_strdup(&str[i]);
	else if (type == 'W')
		map->we_texture = ft_strdup(&str[i]);
	else if (type == 'E')
		map->ea_texture = ft_strdup(&str[i]);
	else
		return (0);
	// reminder to put guardians
	return (1);
}
