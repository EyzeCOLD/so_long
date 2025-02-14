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
static void	draw_img(t_game *game, mlx_image_t *img, int x, int y);

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
				draw_img(game, game->wall, win.x, win.y);
			else
				draw_img(game, game->floor, win.x, win.y);
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
				draw_img(game, game->exit, win.x, win.y);
				draw_img(game, game->exit2, win.x, win.y);
			}
			else if (game->map->grid[map.y][map.x] == 'C')
				draw_img(game, game->collect, win.x, win.y);
			map.x++;
		}
		map.y++;
	}
	win.x = game->map->p_pos.x * 32;
	win.y = game->map->p_pos.y * 32;
	draw_img(game, game->player, win.x, win.y);
}

static void	draw_img(t_game *game, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(game->mlx, img, x, y) < 0)
		close_game(game, 1);
}
