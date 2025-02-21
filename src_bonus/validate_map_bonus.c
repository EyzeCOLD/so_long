/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:09:10 by juaho             #+#    #+#             */
/*   Updated: 2025/02/20 15:53:38 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"
#include "../libft/libft.h"

static int		validate_map_edge(t_map *map);
static void		validate_chars(t_map *map);
static size_t	count_chars(t_map *map, char c);

void	validate_map(t_map *map)
{
	if (validate_map_edge(map) < 0)
		free_map_error_exit(map, "map not square or walled in properly");
	validate_chars(map);
	validate_winnable(map);
}

static int	validate_map_edge(t_map *map)
{
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	while (col < map->w)
		if (map->grid[row][col++] != '1')
			return (-1);
	row++;
	while (row < map->h - 1)
	{
		if (map->grid[row][0] != '1' || map->grid[row][map->w - 1] != '1')
			return (-1);
		row++;
	}
	col = 0;
	while (col < map->w)
		if (map->grid[row][col++] != '1')
			return (-1);
	return (0);
}

static void	validate_chars(t_map *map)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < map->h)
	{
		col = 0;
		while (col < map->w)
			if (ft_strchr(VALID_CHARS, map->grid[row][col++]) == 0)
				free_map_error_exit(map, "map has invalid characters");
		row++;
	}
	if (count_chars(map, 'P') != 1)
		free_map_error_exit(map, "map doesn't have exactly 1 player");
	if (count_chars(map, 'E') != 1)
		free_map_error_exit(map, "map doesn't have exactly 1 exit");
	map->collectibles = count_chars(map, 'C');
	if (map->collectibles == 0)
		free_map_error_exit(map, "map has no collectibles");
}

static size_t	count_chars(t_map *map, char c)
{
	size_t	row;
	size_t	col;
	size_t	ret;

	row = 0;
	ret = 0;
	while (row < map->h)
	{
		col = 0;
		while (col < map->w)
			if (map->grid[row][col++] == c)
				ret++;
		row++;
	}
	return (ret);
}
