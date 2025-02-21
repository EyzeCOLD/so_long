/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_winnable_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:58:06 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 11:02:08 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/so_long_bonus.h"
#include "../libft/libft.h"

static char		**copy_grid(t_map *map);
static size_t	path_finder(int x, int y, char **map_grid);
static void		find_player(t_map *map);

void	validate_winnable(t_map *map)
{
	size_t	path_finder_ret;
	char	**grid_cpy;

	grid_cpy = copy_grid(map);
	if (!grid_cpy)
		free_map_error_exit(map, "copy_grid failed");
	find_player(map);
	path_finder_ret = path_finder(map->p_pos.x, map->p_pos.y, grid_cpy);
	free_grid(grid_cpy);
	if (path_finder_ret % 10 == 0)
		free_map_error_exit(map, "exit out of reach");
	if (path_finder_ret / 10 != map->collectibles)
		free_map_error_exit(map, "collectible(s) out of reach");
}

static void	find_player(t_map *map)
{
	map->p_pos.y = 1;
	while (map->p_pos.y < map->h)
	{
		map->p_pos.x = 1;
		while (map->p_pos.x < map->w - 1)
		{
			if (map->grid[map->p_pos.y][map->p_pos.x] == 'P')
			{
				map->grid[map->p_pos.y][map->p_pos.x] = '0';
				return ;
			}
			map->p_pos.x++;
		}
		map->p_pos.y++;
	}
}

static char	**copy_grid(t_map *map)
{
	size_t	i;
	char	**map_grid;

	map_grid = (char **) ft_calloc(sizeof(char *), map->h + 1);
	if (!map_grid)
		return (NULL);
	i = 0;
	while (i < map->h)
	{
		map_grid[i] = ft_strdup(map->grid[i]);
		if (!map_grid[i])
		{
			free_grid(map_grid);
			return (NULL);
		}
		i++;
	}
	return (map_grid);
}

static size_t	path_finder(int x, int y, char **map_grid)
{
	size_t	ret;
	char	c;

	ret = 0;
	c = map_grid[y][x];
	if (c == 'E')
		ret = 1;
	else if (c == 'C')
		ret = 10;
	else if (c == 'x' || c == '1' || c == 'O')
		return (0);
	map_grid[y][x] = 'x';
	ret += path_finder(x + 1, y, map_grid);
	ret += path_finder(x - 1, y, map_grid);
	ret += path_finder(x, y + 1, map_grid);
	ret += path_finder(x, y - 1, map_grid);
	return (ret);
}
