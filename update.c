/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:48:30 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/26 15:06:23 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

void angle_update(t_cub *cub)
{
	cub->player->rotation_angle +=
		cub->player->turn_direction * cub->player->rotation_speed;
	cub->player->rotation_angle =
		mod(cub->player->rotation_angle, 2 * M_PI);
}

void pos_update(t_cub *cub)
{
	double move_step;
	int grid_i;
	int grid_j;

	move_step = cub->player->walk_direction * cub->player->move_speed;
	grid_i = (cub->player->y +
			  sin(cub->player->rotation_angle + cub->player->walk_angle) * move_step) /
			 BLOCK_SIZE;
	grid_j = (cub->player->x +
			  cos(cub->player->rotation_angle + cub->player->walk_angle) * move_step) /
			 BLOCK_SIZE;
	if (cub->map_items->map[grid_i][grid_j] != 1)
	{
		cub->player->x += cos(cub->player->rotation_angle + cub->player->walk_angle) * move_step;
		cub->player->y += sin(cub->player->rotation_angle + cub->player->walk_angle) * move_step;
	}
}
