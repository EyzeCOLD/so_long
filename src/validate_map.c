/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:09:10 by juaho             #+#    #+#             */
/*   Updated: 2025/02/06 16:51:40 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include "../libft/libft.h"

static int	how_many_chars_in_map(char map[MAX_H][MAX_W + 2], char c);
static void	validate_map_chars(char map[MAX_H][MAX_W + 2]);
static int	validate_map_edge(char map[MAX_H][MAX_W + 2]);


void	validate_map(char map[MAX_H][MAX_W + 2])
{
	int	row;
	int	col;
	int	width;

	width = ft_strlen(map[0]);
	row = 1;
	while (row < MAX_H)
	{
		col = 0;
		while (map[row][col])
		{
			if (!ft_strchr(VALID_CHARS, map[row][col]))
				error_exit("Map not rectangular or has empty/invalid chars");
			col++;
		}
		if (col != width)
			error_exit("Map not rectangular");
		row++;
	}
	if (validate_map_edge(map) < 0)
		error_exit("Map not walled off");
	ft_printf("MAP VALIDATION SUCCESFUL\n");
}

static int	validate_map_edge(char map[MAX_H][MAX_W + 2])
{
	int	row;
	int	col;

	col = 0;
	while (map[0][col] != '\n')
		if (map[0][col++] != '1')
			return (-1);
	row = 1;
	while (map[row][0])
	{
		if (map[row][0] != '1' || map[row][ft_strlen(map[row])] - 1 != '1')
			return (-1);
		row++;
	}
	row--;
	col = 0;
	while (map[row][col] != '\n')
		if (map[row][col++] != '1')
			return (-1);
	return (0);
}

static void	validate_map_chars(char map[MAX_H][MAX_W + 2])
{
	if (how_many_chars_in_map(map, 'P') != 1)
		error_exit("Map has multiple Player Starts (\'P\')");
	if (how_many_chars_in_map(map, 'E') != 1)
		error_exit("Map has multiple Exits (\'E\')");
	if (how_many_chars_in_map(map, 'C') == 0)
		error_exit("Map has no collectibles (\'C\')");
}

static int how_many_chars_in_map(char map[MAX_H][MAX_W + 2], char c)
{
	int	ret;
	int	row;
	int	col;

	ret = 0;
	row = 0;
	col = 0;
	while (map[row])
	{
		while (map[row][col])
		{
			if (map[row][col] == c)
				ret++;
			col++;
		}
		row++;
	}
	return (ret);
}
