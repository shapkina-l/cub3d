/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:54:31 by lshapkin          #+#    #+#             */
/*   Updated: 2025/07/25 19:59:04 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	file_validation(t_game	*game, char *argument)
{
	t_init		init;

	initialize_init(&init);
	if (!build_array_from_file(&init, argument))
		return (free_init(&init), 0);
	if (!validate_cub_elements(&init))
		return (free_init(&init), 0);
	initialize_map(game->map);
	if (!set_map_data(&init, game->map))
		return (free_init(&init), 0);
	if (!validate_map_chars(game->map))
		return (free_init(&init), 0);
	if (!validate_map_boundaries(&init))
		return (free_init(&init), 0);
	find_starting_point(game->map, game->player);
	free_init(&init);
	return (1);
}

int	argument_validation(int arc, char **arv)
{
	if (arc != 2)
		return (error_msg("One .cub file address argument needed."), 0);
	if (!validate_file_format(arv[1]))
		return (error_msg("Argument must be valid .cub file address."), 0);
	return (1);
}
