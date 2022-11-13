/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:48:30 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/12 23:33:39 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

void angle_update(t_cub *mycub)
{
	mycub->player->rotation_angle +=
		mycub->player->turn_direction * mycub->player->rotation_speed;
	mycub->player->rotation_angle =
		mod(mycub->player->rotation_angle, 2 * M_PI);
	// printf("[angle: %f]\n", mycub->player->rotation_angle);
}

void pos_update(t_cub *mycub)
{
	double move_step;
	int grid_i;
	int grid_j;

	move_step = mycub->player->walk_direction * mycub->player->move_speed;
	grid_i = (mycub->player->y +
			sin(mycub->player->rotation_angle
			+ mycub->player->walk_angle) * move_step) / BLOCK_SIZE;
	grid_j = (mycub->player->x +
			cos(mycub->player->rotation_angle
			+ mycub->player->walk_angle) * move_step) / BLOCK_SIZE;
	if (g_map[grid_i][grid_j] != 1)
	{
		mycub->player->x += cos(mycub->player->rotation_angle + mycub->player->walk_angle) * move_step;
		mycub->player->y += sin(mycub->player->rotation_angle + mycub->player->walk_angle) * move_step;
	}
	// printf("[playerx : %f][player.y: %f]\n", mycub->player->x, mycub->player->y);
}
