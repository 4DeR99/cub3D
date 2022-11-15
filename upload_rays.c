/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:29:26 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/15 14:44:56 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

void upload_rays(t_cub *cub)
{
	int ndx;
	double ray_angle;
	t_m_cords ray_cords;

	ray_angle = cub->player->rotation_angle - (FOV_ANGLE / 2);
	ndx = 0;
	rend3R_init(cub);
	while (ndx < cub->num_rays)
	{
		cub->rays[ndx].angle = ray_angle;
		ray_angle += (double)FOV_ANGLE / cub->num_rays;
		ray_cast(cub, ndx);
		rend3r_walls(cub, ndx);
		ndx++;
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_window, cub->rend3D->img,
		0, 0);
	mlx_destroy_image(cub->mlx, cub->rend3D->img);
}
