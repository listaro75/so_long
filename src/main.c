/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:00:33 by luda-cun          #+#    #+#             */
/*   Updated: 2025/04/16 12:45:51 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../so_long.h"
// check name
int check_name_map(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i < 4)
		return (0);
	if (str[i - 4] == '.' && str[i - 3] == 'b' && str[i - 2] == 'e' && str[i - 1] == 'r')
		return (1);
	return (0);	
}
int count_lines(char *str)
{
	int fd;
	char *line;
	int count;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		so_long_error("Error:\nFailed to open the map file\n");
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}
char **init_map(char *str)
{
	int fd;
	char **map;
	char *line;
	int i;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		so_long_error("Error:\nFailed to open the map file\n");
	map = malloc(sizeof(char *) * (count_lines(str) + 1));
	if (!map)
		so_long_error("Error:\nMemory allocation failed\n");
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map[i] = line;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void print_map(char **map)
{
	int i = 0;
	while (map[i])
	{
		ft_printf("%s", map[i]);
		i++;
	}
}

void check_item(t_map *map)
{
	int i=0;
	int j=0;
	int player=0;
	int exit=0;
	int collect=0;

	while (map->map[j])
	{
		i = 0;
		while(map->map[j][i])
		{
			if (map->map[j][i] == 'P')
			{
				map->player_x = i;
				map->player_y = j;
				player++;
			}
			else if (map->map[j][i] == 'E')
			{
				map->exit_x = i;
				map->exit_y = j;
				exit++;
			}
			else if (map->map[j][i] == 'C')
				collect++;
			i++;
		}
		j++;
	}
	if (player != 1 || exit != 1 || collect < 1)
	{
		free_map(map->map);
		so_long_error("Error:\nInvalid number of items in the map\n");
	}
}

int main(int ac, char **av)
{
	t_map map;
	
	if (ac != 2)
		so_long_error("Error:\nWrong number of arguments\n");
	if (check_name_map(av[1]) == 0)
		so_long_error("Error:\nWrong map name\n");
	map.map = init_map(av[1]);
	check_map(&map, av);
	display_window(&map);
	print_map(map.map);
	free_map(map.map);
}
