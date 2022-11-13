/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:40:33 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/12 14:50:00 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

int key_press(int keycode, t_cub *mycub)
{
	if (keycode == ESC)
		exit(1);
	else if (keycode == A)
	{
		mycub->player->walk_direction = 1;
		mycub->player->walk_angle = -M_PI_2;
	}
	else if (keycode == S)
		mycub->player->walk_direction = -1;
	else if (keycode == D)
	{
		mycub->player->walk_direction = 1;
		mycub->player->walk_angle = M_PI_2;
	}
	else if (keycode == W)
		mycub->player->walk_direction = 1;
	else if (keycode == RIGHT)
		mycub->player->turn_direction = 1;
	else if (keycode == LEFT)
		mycub->player->turn_direction = -1;
	pos_update(mycub);
	angle_update(mycub);
	draw_map(mycub);
	draw_player(mycub);
	upload_rays(mycub);
	return 0;
}

int key_release(int keycode, t_cub *mycub)
{
	if (keycode == A || keycode == S || keycode == D || keycode == W)
	{
		mycub->player->walk_direction = 0;
		mycub->player->walk_angle = 0;
	}
	if (keycode == RIGHT || keycode == LEFT)
		mycub->player->turn_direction = 0;
	return 0;
}