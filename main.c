/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:31:46 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/07 20:43:28 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_cub	*cub;

	cub = (t_cub *)calloc(1, sizeof(t_cub));
	protect(cub);
	cub->map_items = parser();
	cub_init(cub);
	sprite_init(cub);
	map_init(cub);
	mlx_hook(cub->mlx_window, 2, 0, key_press, cub);
	mlx_hook(cub->mlx_window, 3, 0, key_release, cub);
	mlx_hook(cub->mlx_window, 6, 0L, mouse_move, cub);
	mlx_loop(cub->mlx);
}
