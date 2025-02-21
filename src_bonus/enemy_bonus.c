/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:55:56 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 12:39:58 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include <stdlib.h>

static void	move_enemy(t_game *game, size_t i);
static void	randomize_direction(t_map *map, t_coord *pos, t_coord *dest);
static void	game_over(t_game *game);

void	update_enemies(t_game *game)
{
	static double	accumulator;
	size_t			i;

	accumulator += game->mlx->delta_time;
	if (accumulator >= ENEMY_TIME)
	{
		i = 0;
		accumulator -= ENEMY_TIME;
		while (i < game->enemy->frames[0]->count)
		{
			move_enemy(game, i);
			i++;
		}
		player_collision(game);
	}
}

static void	move_enemy(t_game *game, size_t i)
{
	t_coord	pos;
	t_coord	dest;

	pos.x = game->enemy->frames[0]->instances[i].x / 32;
	pos.y = game->enemy->frames[0]->instances[i].y / 32;
	randomize_direction(game->map, &pos, &dest);
	move_anim(game->enemy, &pos, dest.x - pos.x, dest.y - pos.y);
	game->map->grid[pos.y][pos.x] = '0';
	game->map->grid[dest.y][dest.x] = 'O';
}

static void	randomize_direction(t_map *map, t_coord *pos, t_coord *dest)
{
	size_t	dir;
	size_t	try_again;

	dir = rand() % 4;
	try_again = 4;
	while (try_again--)
	{
		dest->x = pos->x;
		dest->y = pos->y;
		if (dir == 0)
			dest->x++;
		else if (dir == 1)
			dest->x--;
		else if (dir == 2)
			dest->y++;
		else if (dir == 3)
			dest->y--;
		if (map->grid[dest->y][dest->x] == '0')
			return ;
		dir = (dir + 1) % 4;
	}
	dest->x = pos->x;
	dest->y = pos->y;
}

void	player_collision(t_game *game)
{
	size_t			i;
	t_coord			enemy_pos;
	t_coord			p_pos;
	mlx_instance_t	instance;

	i = 0;
	while (i < game->enemy->frames[0]->count)
	{
		instance = game->enemy->frames[0]->instances[i];
		enemy_pos.x = instance.x / 32;
		enemy_pos.y = instance.y / 32;
		p_pos = game->map->p_pos;
		if (enemy_pos.x == p_pos.x && enemy_pos.y == p_pos.y)
			game_over(game);
		i++;
	}
}

static void	game_over(t_game *game)
{
	ft_printf("GAME OVER\nThe flame of your life has been quenched . . .\n");
	close_game(game, 0);
}
