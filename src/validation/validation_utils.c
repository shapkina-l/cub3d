#include "../../includes/cub3d.h"

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

char	*ft_texture_dup(const char *s)
{
	char	*res;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[len] != ' ' && s[len] != '\0')
		len++;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i != len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
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
		map->no_texture = ft_texture_dup(&str[i]);
	else if (type == 'S')
		map->so_texture = ft_texture_dup(&str[i]);
	else if (type == 'W')
		map->we_texture = ft_texture_dup(&str[i]);
	else if (type == 'E')
		map->ea_texture = ft_texture_dup(&str[i]);
	else
		return (0);
	// reminder to put guardians
	return (1);
}
