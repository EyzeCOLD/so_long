/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:37:54 by juaho             #+#    #+#             */
/*   Updated: 2025/02/21 11:15:38 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"

static t_anim	*tex_to_anim(mlx_texture_t *tex, mlx_t *mlx);
static void		slice_tex(mlx_texture_t *tex, mlx_image_t *img, size_t x);
static t_anim	*new_anim(size_t frame_count, mlx_t *mlx);

int	load_anim(char *filename, mlx_t *mlx, t_anim **anim)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(filename);
	if (!tex)
		return (-1);
	*anim = tex_to_anim(tex, mlx);
	mlx_delete_texture(tex);
	if (!*anim)
		return (-1);
	return (0);
}

static t_anim	*tex_to_anim(mlx_texture_t *tex, mlx_t *mlx)
{
	t_anim		*anim;
	size_t		i;

	i = 0;
	anim = new_anim(tex->width / 32, mlx);
	if (!anim)
		return (NULL);
	while (i < anim->frame_count)
	{
		anim->frames[i] = mlx_new_image(mlx, 32, 32);
		if (!anim->frames[i])
		{
			free_anim(anim);
			return (NULL);
		}
		slice_tex(tex, anim->frames[i], i * 32);
		i++;
	}
	return (anim);
}

static void	slice_tex(mlx_texture_t *tex, mlx_image_t *img, size_t x)
{
	t_coord	i;
	size_t	i_pix;
	size_t	t_pix;

	i.y = 0;
	while (i.y < 32)
	{
		i.x = 0;
		while (i.x < 32)
		{
			i_pix = i.y * 128 + i.x * 4;
			t_pix = i.y * tex->width * 4 + (i.x + x) * 4;
			img->pixels[i_pix] = tex->pixels[t_pix];
			ft_memcpy(&img->pixels[i_pix], &tex->pixels[t_pix], 4);
			i.x++;
		}
		i.y++;
	}
}

static t_anim	*new_anim(size_t frame_count, mlx_t *mlx)
{
	t_anim	*anim;

	anim = ft_calloc(sizeof(t_anim), 1);
	if (!anim)
		return (NULL);
	anim->mlx = mlx;
	anim->frames = ft_calloc(sizeof(mlx_image_t *), frame_count);
	if (!anim->frames)
	{
		free(anim);
		return (NULL);
	}
	anim->frame_count = frame_count;
	anim->frame_index = 0;
	anim->accumulator = 0;
	anim->enabled = 1;
	return (anim);
}

void	free_anim(t_anim *anim)
{
	size_t	i;

	if (!anim)
		return ;
	i = 0;
	while (i < anim->frame_count)
	{
		if (anim->frames[i])
			mlx_delete_image(anim->mlx, anim->frames[i]);
		i++;
	}
	free(anim);
}
