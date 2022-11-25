/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:19:06 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/25 12:27:55 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

static void map_wall_put(t_cub *cub, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < BLOCK_SIZE)
	{
		j = 0;
		while (j < BLOCK_SIZE)
		{
			my_mlx_pixel_put(cub->map_img, x + j, y + i, 0);
			j++;
		}
		i++;
	}
}

static void map_field(t_cub *cub, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < BLOCK_SIZE)
	{
		j = 0;
		if (i == BLOCK_SIZE - 1)
		{
			while (j < BLOCK_SIZE)
			{
				my_mlx_pixel_put(cub->map_img, x + j, y + i, 0);
				j++;
			}
		}
		else
		{
			while (j < BLOCK_SIZE)
			{
				if (j == BLOCK_SIZE - 1)
					my_mlx_pixel_put(cub->map_img, x + j, y + i, 0);
				else
					my_mlx_pixel_put(cub->map_img, x + j, y + i, 0xFFFFFF);
				j++;
			}
		}
		i++;
	}
}

static void set_dot(t_cub *cub)
{
	int x1;
	int y1;
	int r;

	r = 4;
	x1 = 0;
	while (x1 < r)
	{
		y1 = 0;
		while (y1 < r)
		{
			my_mlx_pixel_put(cub->map_img, cub->player->x - 2 + x1,
							 cub->player->y - 2 + y1, 0x0004FD);
			y1++;
		}
		x1++;
	}
}

void map_init(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	cub->map_img->img = mlx_new_image(cub->mlx, BLOCK_SIZE * 15, BLOCK_SIZE * 11);
	if (!cub->map_img->img)
		exit(1);
	cub->map_img->addr = mlx_get_data_addr(cub->map_img->img, &cub->map_img->bits_per_pixel,
										   &cub->map_img->line_length, &cub->map_img->endian);
	if (!cub->map_img->addr)
		exit(1);
	while (i < 11)
	{
		j = 0;
		while (j < 15)
		{
			if (g_map[i][j] == 1)
				map_wall_put(cub, j * BLOCK_SIZE, i * BLOCK_SIZE);
			else
				map_field(cub, j * BLOCK_SIZE, i * BLOCK_SIZE);
			j++;
		}
		i++;
	}
	set_dot(cub);
	upload_rays(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_window,
							cub->map_img->img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->map_img->img);
}
