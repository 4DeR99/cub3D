/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:29:26 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/07 21:05:48 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	edit_ray_type(t_ray ray)
{
	if (ray.door_hit && ray.isFacingUp && ray.type == HORZ)
		return (DOOR_NO);
	else if (ray.door_hit && ray.isFacingDown && ray.type == HORZ)
		return (DOOR_SO);
	else if (ray.door_hit && ray.isFacingLeft && ray.type == VERT)
		return (DOOR_WE);
	else if (ray.door_hit && ray.isFacingRight && ray.type == VERT)
		return (DOOR_EA);
	else if (ray.isFacingUp && ray.type == HORZ)
		return (NO);
	else if (ray.isFacingDown && ray.type == HORZ)
		return (SO);
	else if (ray.isFacingLeft && ray.type == VERT)
		return (WE);
	else if (ray.isFacingRight && ray.type == VERT)
		return (EA);
	return (0);
}

static void	adjust_ray_hit_cords(t_cub *cub, int ndx)
{
	cub->rays[ndx].wallHitX = cub->player->x
		+ cos(cub->rays[ndx].angle) * cub->rays[ndx].dst;
	cub->rays[ndx].wallHitY = cub->player->y
		+ sin(cub->rays[ndx].angle) * cub->rays[ndx].dst;
}

void	upload_rays(t_cub *cub)
{
	int			ndx;
	double		ray_angle;
	t_m_cords	ray_cords;

	ray_angle = cub->player->rotation_angle - (cub->player->fov / 2);
	ndx = 0;
	rend3R_init(cub);
	while (ndx < cub->num_rays)
	{
		cub->rays[ndx].angle = ray_angle;
		cub->rays[ndx].type = ray_cast(cub, ndx);
		cub->rays[ndx].type = edit_ray_type(cub->rays[ndx]);
		adjust_ray_hit_cords(cub, ndx);
		draw_ray(cub, ndx);
		rend3r_walls(cub, ndx);
		ray_angle += (double)cub->player->fov / cub->num_rays;
		ndx++;
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_window, cub->rend3D->img,
		0, 0);
	mlx_destroy_image(cub->mlx, cub->rend3D->img);
	mlx_put_image_to_window(cub->mlx, cub->mlx_window,
		cub->sprite[cub->sprite_ndx].img, 290, 220);
}
