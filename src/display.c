/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:43:38 by luda-cun          #+#    #+#             */
/*   Updated: 2025/04/18 15:27:11 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void display_window(t_map *map)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	map->data = data;
	map->data->mlx = mlx_init();
	map->data->win = mlx_new_window(map->data->mlx, map->width * 64, map->height * 64, "So Long");
	mlx_loop(map->data->mlx);
}
