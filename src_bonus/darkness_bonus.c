/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darkness_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:21:51 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 15:18:29 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../inc/so_long_bonus.h"
#include <math.h>

static void		shade_pixel(unsigned char *pixel, size_t dist);
static size_t	measure_distance(int x1, int x2, int y1, int y2);

void	init_darkness(t_game *game)
{
	t_map			*map;

	map = game->map;
	game->darkness = mlx_new_image(game->mlx, map->w * 32, map->h * 32);
	if (!game->darkness)
		error_close_game(game, NULL);
	update_darkness(game);
}

void	update_darkness(t_game *game)
{
	t_coord			d;
	t_coord			p;
	size_t			dist;
	unsigned char	*pixel;

	p.x = game->map->p_pos.x * 128 + 64;
	p.y = game->map->p_pos.y * 128 + 64;
	d.y = 0;
	while (d.y < game->darkness->height * 4)
	{
		d.x = 0;
		while (d.x < game->darkness->width * 4)
		{
			dist = measure_distance(d.x, p.x, d.y, p.y);
			pixel = &game->darkness->pixels[d.x + d.y * game->darkness->width];
			shade_pixel(pixel, dist);
			d.x = d.x + 4;
		}
		d.y = d.y + 4;
	}
}

static size_t	measure_distance(int x1, int x2, int y1, int y2)
{
	int	a;
	int	b;

	a = pow(abs(x1 - x2), 2);
	b = pow(abs(y1 - y2), 2);
	return (sqrt(a + b));
}

static void	shade_pixel(unsigned char *pixel, size_t dist)
{
	unsigned char	*p;

	p = pixel;
	*p = 0;
	p++;
	*p = 0;
	p++;
	*p = 50;
	p++;
	if (dist < 1024)
		*p = dist / 4;
	else
		*p = 255;
}
