/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:30:39 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 15:38:22 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../inc/so_long_bonus.h"
#include "../libft/libft.h"

static void	update_moves(t_game *game);
static void	collect(t_game *game, t_coord *coord);
static void	open_exit(t_game *game);
static void	win_game(t_game *game);

void	move_player(t_game *game, int x, int y)
{
	t_coord			dest;
	char			c;

	dest.x = game->map->p_pos.x + x;
	dest.y = game->map->p_pos.y + y;
	c = game->map->grid[dest.y][dest.x];
	if (c == '1')
		return ;
	move_anim(game->player, &game->map->p_pos, x, y);
	game->moves++;
	update_moves(game);
	game->map->p_pos.x += x;
	game->map->p_pos.y += y;
	if (c == 'C')
		collect(game, &dest);
	else if (c == 'E' && game->map->exit_open)
		win_game(game);
	else if (c == 'O')
		player_collision(game);
	if (game->nightmode)
		update_darkness(game);
}

static void	update_moves(t_game *game)
{
	char	*num;
	char	*str;

	num = ft_itoa(game->moves);
	if (!num)
		error_close_game(game, "malloc");
	str = ft_strjoin("Moves: ", num);
	if (!str)
		error_close_game(game, "malloc");
	free(num);
	game->movecounter->enabled = 0;
	mlx_delete_image(game->mlx, game->movecounter);
	game->movecounter = mlx_put_string(game->mlx, str, 8, 2);
}

static void	collect(t_game *game, t_coord *coord)
{
	hide_anim_instance(game->collect, coord);
	game->map->grid[coord->y][coord->x] = '0';
	game->map->collectibles--;
	if (game->map->collectibles == 0)
		open_exit(game);
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
