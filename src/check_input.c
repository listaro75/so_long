/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:24:47 by luda-cun          #+#    #+#             */
/*   Updated: 2025/04/16 12:33:01 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	size_wall(char *str, char **map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (free(str), free_map(map),
				so_long_error("Error:\nInvalid wall\n"));
		i++;
	}
}

void	check_wall(t_map *map)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map->map[j][i])
	{
		i = 0;
		line = ft_strtrim(map->map[j], "\n");
		if (j == 0)
			size_wall(line, map->map);
		while (line[i])
		{
			if ((line[i] != '1' && line[i] != '0' && line[i] != 'C'
					&& line[i] != 'E' && line[i] != 'P') || (line[0] != '1'
					|| line[map->width - 1] != '1')
				|| ft_strlen(line) != map->width)
			{
				free(line);
				free_map(map->map);
				so_long_error("Error:\nInvalid character in the map\n");
			}
			i++;
		}
		j++;
		free(line);
	}
	line = ft_strtrim(map->map[j], "\n");
	size_wall(line, map->map);
	free(line);
}

void	check_item_map(char **map, char **freeable)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'P' || map[i][j] == 'E')
			{
				free_map(map);
				free_map(freeable);
				so_long_error("Error:\nInvalid item in the map\n");
			}
			j++;
		}
		i++;
	}
	free_map(map);
}

void	check_map(t_map *map, char **av)
{
	char	*line;
	char	**map_tmp;

	line = ft_strtrim(map->map[0], "\n");
	map->width = ft_strlen(line);
	free(line);
	map->height = count_lines(av[1]);
	check_wall(map);
	check_item(map);
	map_tmp = init_map(av[1]);
	flood_fill(map_tmp, map->player_x, map->player_y);
	check_item_map(map_tmp, map->map);
}



void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'x' || y < 0 || x < 0)
		return ;
	map[y][x] = 'x';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}
