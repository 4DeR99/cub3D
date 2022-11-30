/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:29:26 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/30 14:52:22 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int edit_ray_type(t_ray ray)
{
	if (ray.isFacingUp && ray.type == HORZ)
		return (NO);
	else if (ray.isFacingDown && ray.type == HORZ)
		return (SO);
	else if (ray.isFacingRight && ray.type == VERT)
		return (EA);
	else if (ray.isFacingLeft && ray.type == VERT)
		return (WE);
	return 0;
}

void adjust_ray_hit_cords(t_cub *cub, int ndx)
{
	cub->rays[ndx].wallHitX = cub->player->x + cos(cub->rays[ndx].angle) * cub->rays[ndx].dst;
	cub->rays[ndx].wallHitY = cub->player->y + sin(cub->rays[ndx].angle) * cub->rays[ndx].dst;
}

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
		cub->rays[ndx].type = ray_cast(cub, ndx);
		cub->rays[ndx].type = edit_ray_type(cub->rays[ndx]);
		adjust_ray_hit_cords(cub, ndx);
		// draw_line(cub, cub->player->x + cos(cub->rays[ndx].angle) * cub->rays[ndx].dst,
		// 		  cub->player->y + sin(cub->rays[ndx].angle) * cub->rays[ndx].dst);
		rend3r_walls(cub, ndx);
		ray_angle += (double)FOV_ANGLE / cub->num_rays;
		ndx++;
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_window, cub->rend3D->img,
							0, 0);
	mlx_destroy_image(cub->mlx, cub->rend3D->img);
}
