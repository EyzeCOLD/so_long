/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:03:43 by juaho             #+#    #+#             */
/*   Updated: 2025/02/19 10:44:11 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../inc/so_long_bonus.h"

static void	draw_bg(t_game *game);
static void	draw_objects(t_game *game);
static void	draw_anim(t_game *game);

void	draw_map(t_game *game)
{
	draw_bg(game);
	draw_objects(game);
	draw_anim(game);
}

static void	draw_anim(t_game *game)
{
	size_t	i;
	t_anim	*animation;

	i = 0;
	animation = game->anim1;
	while (i < animation->frame_count)
	{
		mlx_image_to_window(game->mlx, animation->frames[i], 0, 0);
		if (i != 0)
			animation->frames[i]->enabled = 0;
		i++;
	}
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
