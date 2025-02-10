/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:17:43 by juaho             #+#    #+#             */
/*   Updated: 2025/02/06 15:42:57 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "../inc/so_long.h"

static void	set_map_to_null(char map[MAX_H][MAX_W + 2])
{
	int	x;
	int	y;

	y = 0;
	while (y < MAX_H)
	{
		x = 0;
		while (x < MAX_W)
		{
			map[y][x++] = '\0';
		}
		y++;
	}
}

static void	load_map(int fd, char map[MAX_H][MAX_W + 2])
{
	char	*line;
	int		y;

	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line == GNL_ERROR)
			exit(1);
		if (ft_strlen(line) > MAX_W + 1)
		{
			free(line);
			error_exit("Map too wide!");
		}
		if (y >= MAX_H)
		{
			free(line);
			error_exit("Map too high!");
		}
		ft_strlcpy(map[y], line, MAX_W);
		free(line);
		y++;
	}
}

void	init_map(char *file, char map[MAX_H][MAX_W + 2])
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("init_map");
	set_map_to_null(map);
	load_map(fd, map);
	validate_map(map);
}
