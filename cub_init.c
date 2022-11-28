/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:47:43 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/28 12:59:37 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void mem_alloc(t_cub *cub)
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
	cub->walls = (char **)calloc(4, sizeof(char *));
	if (!cub->walls)
		exit(1);
}

static double find_rotation_angle(t_cub *cub)
{
	if (cub->map_items->player_dir == 'N')
		return (3 * M_PI_2);
	if (cub->map_items->player_dir == 'S')
		return (M_PI_2);
	if (cub->map_items->player_dir == 'W')
		return (M_PI);
	return (0);
}

static void adjust_walls(t_cub *cub)
{
	cub->walls[0] = cub->map_items->NO;
	cub->walls[1] = cub->map_items->SO;
	cub->walls[2] = cub->map_items->WE;
	cub->walls[3] = cub->map_items->EA;
}

void cub_init(t_cub *cub)
{
	cub->win_width = 1080;
	cub->win_height = 720;
	cub->num_rays = cub->win_width;
	mem_alloc(cub);
	adjust_walls(cub);
	cub->map_img->img_width = cub->map_items->map_width * BLOCK_SIZE;
	cub->map_img->img_height = cub->map_items->map_height * BLOCK_SIZE;
	cub->player->x = (BLOCK_SIZE * cub->map_items->player_y) + BLOCK_SIZE / 2;
	cub->player->y = (BLOCK_SIZE * cub->map_items->player_x) + BLOCK_SIZE / 2;
	cub->player->rotation_angle = find_rotation_angle(cub);
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
