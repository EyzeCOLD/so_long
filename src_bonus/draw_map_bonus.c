/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:03:43 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 15:38:00 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../inc/so_long_bonus.h"

static void	draw_bg(t_game *game);
static void	draw_objects(t_game *game);
static void	draw_tile(t_game *game, t_coord *coord, char c);

void	draw_map(t_game *game)
{
	draw_bg(game);
	draw_objects(game);
	if (game->nightmode)
	{
		init_darkness(game);
		if (mlx_image_to_window(game->mlx, game->darkness, 0, 0) < 0)
			error_close_game(game, NULL);
	}
	game->movecounter = mlx_put_string(game->mlx, "Moves: 0", 8, 2);
	if (!game->movecounter)
		error_close_game(game, NULL);
}

static void	draw_bg(t_game *game)
{
	t_coord	map;

	map.y = 0;
	while (map.y < game->map->h)
	{
		map.x = 0;
		while (map.x < game->map->w)
		{
			if (game->map->grid[map.y][map.x] == '1')
				draw_tile(game, &map, '1');
			else
				draw_tile(game, &map, '0');
			map.x++;
		}
		map.y++;
	}
}

static void	draw_objects(t_game *game)
{
	t_coord	map;

	map.y = 0;
	while (map.y < game->map->h)
	{
		map.x = 0;
		while (map.x < game->map->w)
		{
			if (game->map->grid[map.y][map.x] == 'E')
			{
				draw_tile(game, &map, 'E');
				draw_tile(game, &map, 'e');
			}
			else if (game->map->grid[map.y][map.x] == 'X')
				draw_tile(game, &map, 'X');
			else if (game->map->grid[map.y][map.x] == 'C')
				draw_tile(game, &map, 'C');
			else if (game->map->grid[map.y][map.x] == 'O')
				draw_tile(game, &map, 'O');
			map.x++;
		}
		map.y++;
	}
	draw_tile(game, &game->map->p_pos, 'P');
}

static void	draw_tile(t_game *game, t_coord *coord, char c)
{
	mlx_t	*mlx;
	size_t	x;
	size_t	y;
	int		ret;

	mlx = game->mlx;
	x = coord->x * 32;
	y = coord->y * 32;
	if (c == '1')
		ret = mlx_image_to_window(mlx, game->wall, x, y);
	else if (c == 'E')
		ret = mlx_image_to_window(mlx, game->exit, x, y);
	else if (c == 'e')
		ret = mlx_image_to_window(mlx, game->exit2, x, y);
	else if (c == 'P')
		ret = anim_to_window(mlx, game->player, x, y);
	else if (c == 'C')
		ret = anim_to_window(mlx, game->collect, x, y);
	else if (c == 'O')
		ret = anim_to_window(mlx, game->enemy, x, y);
	else
		ret = mlx_image_to_window(mlx, game->floor, x, y);
	if (ret < 0)
		error_close_game(game, NULL);
}
