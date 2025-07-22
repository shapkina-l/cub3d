#include "../../includes/cub3d.h"

int	count_lines(char *cub_address)
{
	char	buffer[10001];
	int		count;
	int		bytes;
	int		fd;
	int		i;

	fd = open(cub_address, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 1;
	bytes = read(fd, buffer, 10000);
	while (bytes > 0)
	{
		i = 0;
		while (i < bytes)
		{
			if (buffer[i] == '\n')
				count++;
			i++;
		}
		bytes = read(fd, buffer, 10000);
	}
	close(fd);
	return (count);
}

int	create_array_helper(t_init *data, char *line, int fd)
{
	int		i;

	i = 0;
	while (line)
	{
		data->array[i] = ft_strdup_newline(line);
		if (!data->array[i])
			return (free(line), close(fd), 0);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	data->array[i] = NULL;
	return (1);
}

int	create_array(t_init *data, char *cub_address)
{
	int		fd;
	char	*line;
	int		lines;

	lines = count_lines(cub_address);
	data->array = ft_calloc(lines + 1, sizeof(char *));
	if (!data->array)
		return (0);
	fd = open(cub_address, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!create_array_helper(data, line, fd))
		return (0);
	close(fd);
	return (1);
}
