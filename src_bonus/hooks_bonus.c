/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:13:49 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 10:22:47 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../inc/so_long_bonus.h"

static void	update_animation(t_anim *anim, mlx_t *mlx);

void	close_hook(void *param)
{
	t_game	*game;

	game = param;
	close_game(game, 0);
}

void	input_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_game(game, 0);
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_player(game, -1, 0);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_player(game, 1, 0);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_player(game, 0, -1);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_player(game, 0, 1);
}

void	animation_hook(void *param)
{
	t_game	*game;

	game = param;
	update_animation(game->player, game->mlx);
	update_animation(game->collect, game->mlx);
	if (game->enemy->frames[0]->count)
		update_animation(game->enemy, game->mlx);
}

void	enemy_hook(void *param)
{
	t_game	*game;

	game = param;
	update_enemies(game);
}

static inline void	update_animation(t_anim *anim, mlx_t *mlx)
{
	anim->accumulator += mlx->delta_time;
	while (anim->accumulator >= FRAME_TIME)
	{
		anim->frames[anim->frame_index]->enabled = 0;
		anim->frame_index = (anim->frame_index + 1) % anim->frame_count;
		anim->frames[anim->frame_index]->enabled = 1;
		anim->accumulator -= FRAME_TIME;
	}
}
