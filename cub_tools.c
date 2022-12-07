/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:41:48 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/06 10:47:25 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_color(int *c_arr)
{
	int color;

	color = c_arr[3];
	color <<= 8;
	color += c_arr[0];
	color <<= 8;
	color += c_arr[1];
	color <<= 8;
	color += c_arr[2];
	return color;
}

void	protect(void *p)
{
	if (!p)
	{
		printf("ERROR\n");
		exit(1);
	}
}