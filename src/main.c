#include "../includes/cub3d.h"


void	print_map(t_map *map)
{
	int	j;

	printf("map:\n");
	j = 0;
	while (map->map[j])
	{
		printf("%s\n", map->map[j]);
		j++;
	}
}

void	print_test_map(t_init *init)
{
	int	j;

	printf("test map:\n");
	j = 0;
	while (init->test_map[j])
	{
		printf("%s\n", init->test_map[j]);
		j++;
	}
}

int	main(int arc, char **arv)
{
	t_init		init;
	t_map		map;
	t_player	player;

	if (arc != 2)
		return (ft_printf("Error: one .cub file address argument needed.\n"), 1);
	if (!validate_file_format(arv[1]))
		return (ft_printf("Error: argument must be valid .cub file address.\n"), 1);
	initialize_data(&init);
	if (!create_array(&init, arv[1]))
		return (1);
	if (!validate_cub_elements(&init))
		return (ft_printf("Error: map is invalid.\n"), 1);
	initialize_map(&map);
	if (!set_map_data(&init, &map))
		return (ft_printf("Error: map is invalid.\n"), 1);
	if (!validate_map_chars(&map))
		return (ft_printf("Error: map is invalid.\n"), 1);
	if (!validate_map_chars(&map))
		return (ft_printf("Error: map is invalid.\n"), 1);
	print_map(&map);
	print_test_map(&init);
	if (!validate_map_boundaries(&init))
		return (ft_printf("Error: map is invalid.\n"), 1);
	find_starting_point(&map, &player);
	printf("Data ready to be used for the game!\n");
}
