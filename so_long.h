/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:16:04 by luda-cun          #+#    #+#             */
/*   Updated: 2025/04/16 12:58:14 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/inc/ft_printf.h"
# include "libft/inc/get_next_line.h"
# include "libft/inc/libft.h"
#include "libft/minilibx-linux/mlx.h"
#include "libft/minilibx-linux/mlx_int.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
}			t_data;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		move_count;
	struct	s_data *data;
}			t_map;

// exit_code.c
void		so_long_error(char *str);
void		free_map(char **map);

void		check_map(t_map *map, char **av);
int			count_lines(char *str);
void		check_item(t_map *map);
void		check_wall(t_map *map);
char		**init_map(char *str);
void		flood_fill(char **map, int x, int y);
void		print_map(char **map);
void		display_window(t_map *map);

#endif