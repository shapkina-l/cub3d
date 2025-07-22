#include "../../includes/cub3d.h"

static int	skip_spaces(const char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

static int	skip_digits(const char *str, int i)
{
	int	start;

	start = i;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i > start)
		return (i);
	else
		return (-1);
}

int colour_verification(const char *str)
{
		int	i;
	int	count;

	i = 0;
	count = 0;
	while (count < 3)
	{
		i = skip_spaces(str, i);
		i = skip_digits(str, i);
		if (i == -1)
			return (0);
		i = skip_spaces(str, i);
		if (count < 2)
		{
			if (str[i] != ',')
				return (0);
			i++;
		}
		count++;
	}
	i = skip_spaces(str, i);
	if (str[i] != '\0')
		return (0);
	return (1);
}
