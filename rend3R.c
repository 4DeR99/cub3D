/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend3R.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:08:07 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/25 10:49:42 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

void rend3r_walls(t_cub *cub, int ndx)
{
	double dst_2_plan;
	double wall_height;
	double	correct_dst;
	t_cords cord1;
	t_cords cord2;

	correct_dst = 4 * cub->rays[ndx].dst * cos(cub->rays[ndx].angle
			- cub->player->rotation_angle);
	dst_2_plan = (cub->win_width / 2) / tan(FOV_ANGLE / 2);
	wall_height = (REAL_BLOCK_SIZE / correct_dst) * dst_2_plan;
	cord1.x = ndx * WALL_STRIP_WIDTH;
	cord1.y = (cub->win_height / 2) - (wall_height / 2);
	cord2.x = cord1.x + WALL_STRIP_WIDTH;
	cord2.y = (cub->win_height / 2) + (wall_height / 2);
	draw_rect(cub, cord1, cord2, 0);
}

void rend3R_init(t_cub *cub)
{
	cub->rend3D->img = mlx_new_image(cub->mlx, cub->win_width,
			cub->win_height);
	if (!cub->rend3D->img)
		exit(1);
	cub->rend3D->addr = mlx_get_data_addr(cub->rend3D->img,
			&cub->rend3D->bits_per_pixel, &cub->rend3D->line_length,
			&cub->rend3D->endian);
	if (!cub->rend3D->addr)
		exit(1);
}