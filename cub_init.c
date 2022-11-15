/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:47:43 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/15 15:02:15 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

void cub_init(t_cub *cub)
{
	cub->win_width = 1080;
	cub->win_heigh = 720;
	cub->player = (t_p_data *)calloc(1, sizeof(t_p_data));
	cub->player->x = (BLOCK_SIZE * 15) / 2;
	cub->player->y = (BLOCK_SIZE * 11) / 2;
	cub->player->rotation_angle = 0;
	cub->player->walk_direction = 0;
	cub->player->turn_direction = 0;
	cub->player->walk_angle = 0;
	cub->player->move_speed = 0.7;
	cub->player->rotation_speed = 2 * (M_PI / 180);
	cub->num_rays = cub->win_width / WALL_STRIP_WIDTH;
	cub->map = (t_data *)calloc(1, sizeof(t_data));
	cub->rays = (t_ray *)calloc(cub->num_rays, sizeof(t_ray));
	cub->rend3D = (t_data *)calloc(1, sizeof(t_data));
	cub->mlx = mlx_init();
	cub->mlx_window = mlx_new_window(cub->mlx, cub->win_width,
									cub->win_heigh, "cub3D");
}
