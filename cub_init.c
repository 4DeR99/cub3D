/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:47:43 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/25 12:32:57 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

void mem_alloc(t_cub *cub)
{
	cub->player = (t_p_data *)calloc(1, sizeof(t_p_data));
	if (!cub->player)
		exit(1);
	cub->map_img = (t_data *)calloc(1, sizeof(t_data));
	if (!cub->map_img)
		exit(1);
	cub->rays = (t_ray *)calloc(cub->num_rays, sizeof(t_ray));
	if (!cub->rays)
		exit(1);
	cub->rend3D = (t_data *)calloc(1, sizeof(t_data));
	if (!cub->rend3D)
		exit(1);
}

void cub_init(t_cub *cub)
{
	cub->win_width = 1080;
	cub->win_height = 720;
	cub->num_rays = cub->win_width / WALL_STRIP_WIDTH;
	mem_alloc(cub);
	cub->player->x = (BLOCK_SIZE * 15) / 2;
	cub->player->y = (BLOCK_SIZE * 11) / 2;
	cub->player->rotation_angle = M_PI_2;
	cub->player->walk_direction = 0;
	cub->player->turn_direction = 0;
	cub->player->walk_angle = 0;
	cub->player->move_speed = 1.6;
	cub->player->rotation_speed = 2 * (M_PI / 180);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit(1);
	cub->mlx_window = mlx_new_window(cub->mlx, cub->win_width,
									cub->win_height, "cub3D");
	if (!cub->mlx_window)
		exit(1);
}
