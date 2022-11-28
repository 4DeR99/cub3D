/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:43:50 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/28 11:54:14 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (fabs(x2 - cub->player->x) >= fabs(y2 - cub->player->y))
		step = fabs(x2 - cub->player->x);
	else
		step = fabs(y2 - cub->player->y);
	xin = (float)(x2 - cub->player->x) / step;
	yin = (float)(y2 - cub->player->y) / step;
	x2 = cub->player->x;
	y2 = cub->player->y;
	k = 0;
	while (k++ < step)
	{
		x2 += xin;
		y2 += yin;
		my_mlx_pixel_put(cub->map_img, x2, y2, 0xFD0000);
	}
}

void draw_rect(t_cub *cub, t_cords cord1, t_cords cord2, double c)
{
	double x;
	double y;

	if (cord1.x < 0)
		cord1.x = 0;
	if (cord1.y < 0)
		cord1.y = 0;
	if (cord2.x > cub->win_width)
		cord2.x = cub->win_width;
	if (cord2.y > cub->win_height)
		cord2.y = cub->win_height;
	y = cord1.y;
	while (y < cord2.y)
	{
		x = cord1.x;
		while (x < cord2.x)
			my_mlx_pixel_put(cub->rend3D, x++, y, 0x00fff0ff - c);
		y++;
	}
}

void fill_floor_nd_ceiling(t_cub *cub, int c_color, int f_color)
{
	int ndx;
	int jdx;

	ndx = 0;
	while (ndx < (cub->win_height / 2))
	{
		jdx = 0;
		while (jdx < cub->win_width)
			my_mlx_pixel_put(cub->rend3D, jdx++, ndx, f_color);
		ndx++;
	}
	ndx = cub->win_height / 2;
	while (ndx < cub->win_height)
	{
		jdx = 0;
		while (jdx < cub->win_width)
			my_mlx_pixel_put(cub->rend3D, jdx++, ndx, c_color);
		ndx++;
	}
}
