/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:43:50 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/13 18:05:28 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_map(t_cub *mycub)
{
	int i;
	int j;

	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 15)
		{
			if (g_map[i][j] == 1)
				mlx_put_image_to_window(mycub->mlx, mycub->mlx_window,
					mycub->map->wall->img, j * BLOCK_SIZE, i * BLOCK_SIZE);
			else
				mlx_put_image_to_window(mycub->mlx, mycub->mlx_window,
					mycub->map->empty->img, j * BLOCK_SIZE, i * BLOCK_SIZE);
			j++;
		}
		i++;
	}
}

void	draw_line(t_cub *mycub, double x2, double y2)
{
	double	step;
	double	xin;
	double	yin;
	int		k;

	if (x2 - mycub->player->x >= y2 - mycub->player->y)
		step = x2 - mycub->player->x;
	else
		step = y2 - mycub->player->y;
	xin = (x2 - mycub->player->x) / step;
	yin = (y2 - mycub->player->y) / step;
	x2 = mycub->player->x;
	y2 = mycub->player->y;
	while (k++ < step)
	{
		x2 += xin;
		y2 += yin;
		my_mlx_pixel_put(mycub->ray_2_put, x2, y2, 10);
	}
	mlx_put_image_to_window(mycub->mlx, mycub->mlx_window, mycub->ray_2_put->img, 100, 100);
}

void draw_player(t_cub *mycub)
{
	mlx_put_image_to_window(mycub->mlx, mycub->mlx_window, mycub->player->dot->img,
		mycub->player->x - 3, mycub->player->y - 3);
}