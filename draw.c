/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:43:50 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/15 15:07:58 by moulmado         ###   ########.fr       */
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

void draw_line(t_cub *cub, double x2, double y2)
{
	double step;
	double xin;
	double yin;
	int k;

	if (x2 - cub->player->x >= y2 - cub->player->y)
		step = x2 - cub->player->x;
	else
		step = y2 - cub->player->y;
	xin = (x2 - cub->player->x) / step;
	yin = (y2 - cub->player->y) / step;
	x2 = cub->player->x;
	y2 = cub->player->y;
	while (k++ < step)
	{
		x2 += xin;
		y2 += yin;
		my_mlx_pixel_put(cub->map, x2, y2, 0xFD0000);
	}
}

void	draw_rect(t_cub *cub, t_cords cord1, t_cords cord2)
{
	double	x;
	double	y;

	y = cord1.y;
	while (y < cord2.y)
	{
		x = cord1.x;
		while(x < cord2.x)
			my_mlx_pixel_put(cub->rend3D, x++, y, 0x00D7FD);
		y++;
	}
}
