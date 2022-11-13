/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:47:43 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/13 18:04:16 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

static void map_wall_setup(t_cub *mycub)
{
	int i;
	int j;

	mycub->map->wall = (t_data *)calloc(1, sizeof(t_data));
	mycub->map->empty = (t_data *)calloc(1, sizeof(t_data));
	mycub->map->wall->img = mlx_new_image(mycub->mlx, BLOCK_SIZE, BLOCK_SIZE);
	mycub->map->wall->addr = mlx_get_data_addr(mycub->map->wall->img,
			&mycub->map->wall->bits_per_pixel, &mycub->map->wall->line_length,
			&mycub->map->wall->endian);
	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
			my_mlx_pixel_put(mycub->map->wall, i, j++, 0);
		i++;
	}
}

static void map_empty_setup(t_cub *mycub)
{
	int i;
	int j;

	i = 0;
	mycub->map->empty->img = mlx_new_image(mycub->mlx, BLOCK_SIZE, BLOCK_SIZE);
	mycub->map->empty->addr = mlx_get_data_addr(mycub->map->empty->img,
			&mycub->map->empty->bits_per_pixel, &mycub->map->empty->line_length,
			&mycub->map->empty->endian);
	while (i < BLOCK_SIZE)
	{
		j = 0;
		if (i == BLOCK_SIZE-1)
			while (j < BLOCK_SIZE)
				my_mlx_pixel_put(mycub->map->empty, j++, i, 0);
		else
		{
			while (j < BLOCK_SIZE)
			{
				if (j == BLOCK_SIZE-1)
					my_mlx_pixel_put(mycub->map->empty, j++, i, 0);
				else
					my_mlx_pixel_put(mycub->map->empty, j++, i, 0xFFFFFF);
			}
		}
		i++;
	}
}

static void set_dot(t_cub *mycub)
{
	int x1;
	int y1;
	int r;

	r = 6;
	mycub->player->dot = (t_data *)calloc(1, sizeof(t_data));
	mycub->player->dot->img = mlx_new_image(mycub->mlx, r, r);
	mycub->player->dot->addr = mlx_get_data_addr(mycub->player->dot->img,
			&mycub->player->dot->bits_per_pixel,
			&mycub->player->dot->line_length, &mycub->player->dot->endian);
	x1 = 0;
	while (x1 < r)
	{
		y1 = 0;
		while (y1 < r)
			my_mlx_pixel_put(mycub->player->dot, x1, y1++, 0x0004FD);
		x1++;
	}
}

static void	set_pxl(t_cub *mycub)
{
	mycub->ray_2_put = (t_data *)calloc(1, sizeof(t_data));
	mycub->ray_2_put->img = mlx_new_image(mycub->mlx, mycub->win_width, mycub->win_heigh);
	mycub->ray_2_put->addr = mlx_get_data_addr(mycub->ray_2_put->img,
			&mycub->ray_2_put->bits_per_pixel, &mycub->ray_2_put->line_length,
			&mycub->ray_2_put->endian);
}

void cub_init(t_cub *mycub)
{
	mycub->win_width = 1080;
	mycub->win_heigh = 720;
	mycub->player = (t_p_data *)calloc(1, sizeof(t_p_data));
	mycub->player->x = (BLOCK_SIZE * 15) / 2;
	mycub->player->y = (BLOCK_SIZE * 11) / 2;
	mycub->player->rotation_angle = M_PI_2;
	mycub->player->walk_direction = 0;
	mycub->player->turn_direction = 0;
	mycub->player->walk_angle = 0;
	mycub->player->move_speed = 3;
	mycub->player->rotation_speed = 2 * (M_PI / 180);
	mycub->num_rays = mycub->win_width / WALL_STRIP_WIDTH;
	mycub->map = (t_map *)calloc(1, sizeof(t_map));
	mycub->rays = (t_ray *)calloc(mycub->num_rays, sizeof(t_ray));
	mycub->mlx = mlx_init();
	mycub->mlx_window = mlx_new_window(mycub->mlx, mycub->win_width,
			mycub->win_heigh, "cub3D");
	map_wall_setup(mycub);
	map_empty_setup(mycub);
	set_dot(mycub);
	set_pxl(mycub);
}
