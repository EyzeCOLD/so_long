/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:17:43 by juaho             #+#    #+#             */
/*   Updated: 2025/02/13 14:43:11 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../inc/so_long.h"

static void	load_map(char *file, t_map *map);
static void	get_map_dimensions(t_map *map);
static void	validate_filename(char *file);

void	init_map(char *file, t_map *map)
{
	validate_filename(file);
	map->name = file;
	load_map(file, map);
	get_map_dimensions(map);
	validate_map(map);
	map->exit_open = 0;
}

void	free_grid(char **grid)
{
	size_t	i;

	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

static void	validate_filename(char *file)
{
	size_t	len;

	if (!file)
		error_exit("filename NULL");
	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(file + len - 4, ".ber", 5))
		error_exit("map has to be a .ber file");
}

static void	load_map(char *file, t_map *map)
{
	ssize_t	read_ret;
	char	buf[(MAX_W * (MAX_H + 1)) + 1];
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("could not open map");
	ft_bzero(buf, (MAX_W * (MAX_H + 1)) + 1);
	read_ret = read(fd, buf, (MAX_W * (MAX_H + 1)) + 1);
	close(fd);
	if (read_ret < 0)
		error_exit("could not read map");
	if (buf[MAX_W * (MAX_H + 1)] != '\0')
		error_exit("map too large");
	if (*buf == '\n' || ft_strnstr(buf, "\n\n", MAX_W * (MAX_H + 1)))
		error_exit("map has an empty line");
	map->grid = ft_split(buf, '\n');
	if (!map->grid)
		error_exit("ft_split failed");
	if (!map->grid[0])
		free_map_error_exit(map, "empty map");
}

static void	get_map_dimensions(t_map *map)
{
	map->w = ft_strlen(map->grid[0]);
	if (map->w > MAX_W)
		free_map_error_exit(map, "map too wide");
	map->h = 0;
	while (map->grid[map->h])
	{
		if (ft_strlen(map->grid[map->h]) != map->w)
			free_map_error_exit(map, "map width inconsistent");
		map->h++;
	}
	if (map->h > MAX_H)
		free_map_error_exit(map, "map too tall");
}
