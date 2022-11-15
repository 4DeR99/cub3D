/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:40:33 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/15 14:17:42 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

int key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		exit(0);
	else if (keycode == A)
	{
		cub->player->walk_direction = 1;
		cub->player->walk_angle = -M_PI_2;
	}
	else if (keycode == S)
		cub->player->walk_direction = -1;
	else if (keycode == D)
	{
		cub->player->walk_direction = 1;
		cub->player->walk_angle = M_PI_2;
	}
	else if (keycode == W)
		cub->player->walk_direction = 1;
	else if (keycode == RIGHT)
		cub->player->turn_direction = 1;
	else if (keycode == LEFT)
		cub->player->turn_direction = -1;
	pos_update(cub);
	angle_update(cub);
	map_init(cub);
	return 0;
}

int key_release(int keycode, t_cub *cub)
{
	if (keycode == A || keycode == S || keycode == D || keycode == W)
	{
		cub->player->walk_direction = 0;
		cub->player->walk_angle = 0;
	}
	if (keycode == RIGHT || keycode == LEFT)
		cub->player->turn_direction = 0;
	return 0;
}