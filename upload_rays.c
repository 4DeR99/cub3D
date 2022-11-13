/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:29:26 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/12 15:07:47 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

void upload_rays(t_cub *mycub)
{
	int ndx;
	double ray_angle;

	ray_angle = mycub->player->rotation_angle - (FOV_ANGLE / 2);
	ndx = 0;
	while (ndx < mycub->num_rays)
	{
		mycub->rays[ndx].angle = ray_angle;
		ray_angle += (double)FOV_ANGLE / mycub->num_rays;
		ray_cast(mycub, ndx);
		ndx++;
	}
}
