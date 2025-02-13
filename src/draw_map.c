/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:03:43 by juaho             #+#    #+#             */
/*   Updated: 2025/02/13 14:03:49 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../inc/so_long.h"

static void	draw_bg(t_game *game);
static void	draw_objects(t_game *game);

void	draw_map(t_game *game)
{
	draw_bg(game);
	draw_objects(game);
}

static void	draw_bg(t_game *game)
{
	t_coord	map;
	t_coord	win;

	map.y = 0;
	while (map.y < game->map->h)
	{
		map.x = 0;
		while (map.x < game->map->w)
		{
			win.x = map.x * 32;
			win.y = map.y * 32;
			if (game->map->grid[map.y][map.x] == '1')
				mlx_image_to_window(game->mlx, game->wall, win.x, win.y);
			else
				mlx_image_to_window(game->mlx, game->floor, win.x, win.y);
			map.x++;
		}
		map.y++;
	}
}

static void	draw_objects(t_game *game)
{
	t_coord	map;
	t_coord	win;

	map.y = 0;
	while (map.y < game->map->h)
	{
		map.x = 0;
		while (map.x < game->map->w)
		{
			win.x = map.x * 32;
			win.y = map.y * 32;
			if (game->map->grid[map.y][map.x] == 'E')
			{
				mlx_image_to_window(game->mlx, game->exit, win.x, win.y);
				mlx_image_to_window(game->mlx, game->exit2, win.x, win.y);
			}
			else if (game->map->grid[map.y][map.x] == 'C')
				mlx_image_to_window(game->mlx, game->collect, win.x, win.y);
			map.x++;
		}
		map.y++;
	}
	win.x = game->map->p_pos.x * 32;
	win.y = game->map->p_pos.y * 32;
	mlx_image_to_window(game->mlx, game->player, win.x, win.y);
}
