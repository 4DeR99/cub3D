/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:06:50 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/12 23:27:52 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

static void add_hsteps_till_wall(t_cords *horz, t_cub *mycub, int ndx)
{
	horz->wallhitx = 0;
	horz->wallhity = 0;
	while (horz->xinter >=0 && horz->xinter <= mycub->win_width
		&& horz->yinter >= 0 && horz->yinter <= mycub->win_heigh)
	{
		if (map_has_wall_at(mycub, horz->xinter,
			horz->yinter - mycub->rays[ndx].isFacingUp))
		{
			horz->wallhitx = horz->xinter;
			horz->wallhity = horz->yinter;
			break;
		}
		else
		{
			horz->xinter += horz->xstep;
			horz->yinter += horz->ystep;
		}
	}
}

static t_cords get_horz_cords(t_cub *mycub, int ndx)
{
	t_cords horz;

	horz.yinter = floor(mycub->player->y / BLOCK_SIZE) * BLOCK_SIZE;
	if (mycub->rays[ndx].isFacingDown)
		horz.yinter += BLOCK_SIZE;
	horz.xinter = mycub->player->x
			+ (horz.yinter - mycub->player->y) / tan(mycub->rays[ndx].angle);
	horz.ystep = BLOCK_SIZE;
	if (mycub->rays[ndx].isFacingUp)
		horz.ystep *= -1;
	horz.xstep = BLOCK_SIZE / tan(mycub->rays[ndx].angle);
	if (mycub->rays[ndx].isFacingLeft && horz.xstep > 0)
		horz.xstep *= -1;
	if (mycub->rays[ndx].isFacingRight && horz.xstep < 0)
		horz.xstep *= -1;
	add_hsteps_till_wall(&horz, mycub, ndx);
	return (horz);
}

static void	add_vsteps_till_wall(t_cords *vert, t_cub *mycub, int ndx)
{
	vert->wallhitx = 0;
	vert->wallhity = 0;
	while (vert->xinter >= 0 && vert->xinter <= mycub->win_width
		&& vert->yinter >= 0 && vert->yinter <= mycub->win_heigh)
	{
		if (map_has_wall_at(mycub, vert->xinter - mycub->rays[ndx].isFacingLeft,
			vert->yinter))
		{
			vert->wallhitx = vert->xinter;
			vert->wallhity = vert->yinter;
			break;
		}
		else
		{
			vert->xinter += vert->xstep;
			vert->yinter += vert->ystep;
		}
	}
}

static t_cords	get_vert_cords(t_cub *mycub, int ndx)
{
	t_cords	vert;

	vert.xinter = floor(mycub->player->x / BLOCK_SIZE) * BLOCK_SIZE;
	if (mycub->rays[ndx].isFacingRight)
		vert.xinter += BLOCK_SIZE;
	vert.yinter = mycub->player->y
			+ (vert.xinter - mycub->player->x) * tan(mycub->rays[ndx].angle);
	vert.xstep = BLOCK_SIZE;
	if (mycub->rays[ndx].isFacingLeft)
		vert.xstep *= -1;
	vert.ystep = BLOCK_SIZE * tan(mycub->rays[ndx].angle);
	if (mycub->rays[ndx].isFacingUp && vert.ystep > 0)
		vert.ystep *= -1;
	if (mycub->rays[ndx].isFacingDown && vert.ystep < 0)
		vert.ystep *= -1;
	add_vsteps_till_wall(&vert, mycub, ndx);
	return (vert);
}

void ray_cast(t_cub *mycub, int ndx)
{
	t_cords horz;
	t_cords vert;

	mycub->rays[ndx].angle = mod(mycub->rays[ndx].angle, 2 * M_PI);
	mycub->rays[ndx].dst = 0;
	mycub->rays[ndx].wallHitX = 0;
	mycub->rays[ndx].wallHitY = 0;
	mycub->rays[ndx].isFacingDown =
		mycub->rays[ndx].angle > 0 && mycub->rays[ndx].angle < M_PI;
	mycub->rays[ndx].isFacingUp = !mycub->rays[ndx].isFacingDown;
	mycub->rays[ndx].isFacingLeft =
		mycub->rays[ndx].angle > M_PI_2 && mycub->rays[ndx].angle < 3 * M_PI_2;
	mycub->rays[ndx].isFacingRight = !mycub->rays[ndx].isFacingLeft;
	horz = get_horz_cords(mycub, ndx);
	vert = get_vert_cords(mycub, ndx);
	horz.dst = dst_between_points(mycub->player->x, mycub->player->y,
			horz.wallhitx, horz.wallhity);
	vert.dst = dst_between_points(mycub->player->x, mycub->player->y,
			vert.wallhitx, vert.wallhity);
	if (horz.dst < vert.dst){
		// mlx_put_image_to_window(mycub->mlx, mycub->mlx_window, mycub->player->dot->img,
		// 	horz.wallhitx - 3, horz.wallhity - 3);
		draw_line(mycub, horz.wallhitx, horz.wallhity);
	}
	else{
		// mlx_put_image_to_window(mycub->mlx, mycub->mlx_window, mycub->player->dot->img,
		// 	vert.wallhitx - 3, vert.wallhity - 3);
		draw_line(mycub, vert.wallhitx, vert.wallhity);
	}
}
