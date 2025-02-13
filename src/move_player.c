/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:30:39 by juaho             #+#    #+#             */
/*   Updated: 2025/02/13 14:17:28 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include "../libft/libft.h"

static void	collect(t_game *game, t_coord *coord);
static void	open_exit(t_game *game);
static void	win_game(t_game *game);

void	move_player(t_game *game, int x, int y)
{
	static size_t	moves;
	t_coord			dest;
	char			c;

	dest.x = game->map->p_pos.x + x;
	dest.y = game->map->p_pos.y + y;
	c = game->map->grid[dest.y][dest.x];
	if (c == '1')
		return ;
	moves++;
	ft_printf("Moves: %u\n", moves);
	game->map->p_pos.x += x;
	game->map->p_pos.y += y;
	game->player->instances[0].x += x * 32;
	game->player->instances[0].y += y * 32;
	if (c == 'C')
		collect(game, &dest);
	else if (c == 'E' && game->map->exit_open)
		win_game(game);
}

static void	collect(t_game *game, t_coord *coord)
{
	t_coord	instance;
	size_t	i;

	i = 0;
	while (i < game->collect->count)
	{
		instance.x = game->collect->instances[i].x / 32;
		instance.y = game->collect->instances[i].y / 32;
		if (instance.x == coord->x && instance.y == coord->y)
		{
			game->map->grid[coord->y][coord->x] = '0';
			game->collect->instances[i].enabled = false;
			game->map->collectibles--;
			if (game->map->collectibles == 0)
				open_exit(game);
		}
		i++;
	}
}

static void	open_exit(t_game *game)
{
	game->map->exit_open = 1;
	game->exit2->instances[0].enabled = false;
}

static void	win_game(t_game *game)
{
	ft_printf("YOU ARE A WINNER\nThanks for playing!\n");
	close_game(game, 0);
}
