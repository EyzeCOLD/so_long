/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:56:21 by juaho             #+#    #+#             */
/*   Updated: 2025/02/20 14:57:42 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../inc/so_long_bonus.h"

static int	find_instance_by_coord(t_anim *anim, t_coord *coord);

int	anim_to_window(mlx_t *mlx, t_anim *anim, size_t x, size_t y)
{
	size_t	i;

	i = 0;
	while (i < anim->frame_count)
	{
		if (mlx_image_to_window(mlx, anim->frames[i], x, y) < 0)
			return (-1);
		if (i != 0)
			anim->frames[i]->enabled = 0;
		i++;
	}
	return (0);
}

void	move_anim(t_anim *anim, t_coord *coord, int x, int y)
{
	size_t	frame_i;
	int		instance_i;

	instance_i = 0;
	if (anim->frames[0]->count > 1)
	{
		instance_i = find_instance_by_coord(anim, coord);
	}
	frame_i = 0;
	while (frame_i < anim->frame_count)
	{
		anim->frames[frame_i]->instances[instance_i].x += x * 32;
		anim->frames[frame_i]->instances[instance_i].y += y * 32;
		frame_i++;
	}
}

void	hide_anim_instance(t_anim *anim, t_coord *coord)
{
	size_t		frame_i;
	int			i;

	frame_i = 0;
	i = find_instance_by_coord(anim, coord);
	if (i < 0)
	{
		return ;
	}
	while (frame_i < anim->frame_count)
		anim->frames[frame_i++]->instances[i].enabled = 0;
}

static inline int	find_instance_by_coord(t_anim *anim, t_coord *coord)
{
	mlx_image_t	*img;
	t_coord		instance;
	int			i;

	i = 0;
	img = anim->frames[0];
	while (i < (int) img->count)
	{
		instance.x = img->instances[i].x;
		instance.y = img->instances[i].y;
		if (instance.x == coord->x * 32 && instance.y == coord->y * 32)
			return (i);
		i++;
	}
	return (-1);
}
