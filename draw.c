/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:43:50 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/07 20:40:26 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_ray(t_cub *cub, int ndx)
{
	double	step;
	t_ratio	in;
	t_ratio	cord;
	int		k;

	cord.x = 12 * BLOCK_SIZE + cub->rays[ndx].dst * cos(cub->rays[ndx].angle);
	cord.y = 7 * BLOCK_SIZE + cub->rays[ndx].dst * sin(cub->rays[ndx].angle);
	if (fabs(cord.x - (12 * BLOCK_SIZE)) >= fabs(cord.y - (7 * BLOCK_SIZE)))
		step = fabs(cord.x - (12 * BLOCK_SIZE));
	else
		step = fabs(cord.y - (7 * BLOCK_SIZE));
	in.x = (float)(cord.x - (12 * BLOCK_SIZE)) / step;
	in.y = (float)(cord.y - (7 * BLOCK_SIZE)) / step;
	cord.x = 12 * BLOCK_SIZE;
	cord.y = 7 * BLOCK_SIZE;
	k = 0;
	while (k++ < step && cord.x < 24*BLOCK_SIZE && cord.y < 14*BLOCK_SIZE)
	{
		cord.x += in.x;
		cord.y += in.y;
		my_mlx_pixel_put(cub->map_img, cord.x, cord.y, 0x00FFE8);
	}
}

static double	find_x_of_wall(t_cub *cub, int ndx)
{
	if (cub->rays[ndx].type == DOOR_NO)
		return (cub->rays[ndx].type = DOOR,
			mod(cub->rays[ndx].wallHitX, BLOCK_SIZE));
	else if (cub->rays[ndx].type == DOOR_SO)
		return (cub->rays[ndx].type = DOOR,
			BLOCK_SIZE - mod(cub->rays[ndx].wallHitX, BLOCK_SIZE));
	else if (cub->rays[ndx].type == DOOR_WE)
		return (cub->rays[ndx].type = DOOR,
			BLOCK_SIZE - mod(cub->rays[ndx].wallHitY, BLOCK_SIZE));
	else if (cub->rays[ndx].type == DOOR_EA)
		return (cub->rays[ndx].type = DOOR,
			mod(cub->rays[ndx].wallHitY, BLOCK_SIZE));
	else if (cub->rays[ndx].type == NO)
		return (mod(cub->rays[ndx].wallHitX, BLOCK_SIZE));
	else if (cub->rays[ndx].type == SO)
		return (BLOCK_SIZE - mod(cub->rays[ndx].wallHitX, BLOCK_SIZE));
	else if (cub->rays[ndx].type == WE)
		return (BLOCK_SIZE - mod(cub->rays[ndx].wallHitY, BLOCK_SIZE));
	else if (cub->rays[ndx].type == EA)
		return (mod(cub->rays[ndx].wallHitY, BLOCK_SIZE));
	return (0);
}

void	draw_vert_line(t_cub *cub, double y1, double y2, int ndx)
{
	t_ratio	cord;
	t_ratio	r;
	int		j;
	int		i;

	cord.x = find_x_of_wall(cub, ndx);
	cord.y = 0;
	r.x = cub->walls[cub->rays[ndx].type].img_width / (BLOCK_SIZE);
	r.y = cub->walls[cub->rays[ndx].type].img_height / (y2 - y1);
	if (y1 < 0)
	{
		cord.y = -y1;
		y1 = 0;
	}
	if (y2 > cub->win_height)
		y2 = cub->win_height;
	while (y1 < y2)
	{
		j = (float)cord.y * r.y;
		j *= cub->walls[cub->rays[ndx].type].img_width;
		i = (float)cord.x * r.x;
		my_mlx_pixel_put(cub->rend3D, ndx, y1++,
			cub->walls[cub->rays[ndx].type].colors[j + i]);
		cord.y++;
	}
}

void	fill_floor_nd_ceiling(t_cub *cub, int c_color, int f_color)
{
	int	ndx;
	int	jdx;

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
