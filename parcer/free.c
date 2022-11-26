/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:02:24 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/25 13:02:51 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void free_str(char **tab)
{
	int x = 0;
	while (tab[x])
		free(tab[x++]);
	free(tab);
}
void free_map_items(t_item *item)
{
	free_str(item->map);
}