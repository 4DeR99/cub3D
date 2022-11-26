/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:16:33 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/26 15:05:19 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_map[11][15];

int map_has_wall_at(t_cub *cub, double x, double y)
{
	int grid_i;
	int grid_j;

	grid_i = y / BLOCK_SIZE;
	grid_j = x / BLOCK_SIZE;
	// printf("[%d][%d]\n", grid_i, grid_j);
	return (cub->map_items->map[grid_i][grid_j] - '0');
}