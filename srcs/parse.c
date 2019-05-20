/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 03:56:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:58:19 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_map_color(t_fdf *u)
{
	int			x;
	int			y;
	t_map		*map;

	map = u->map;
	y = 0;
	while (y < map->nb_row)
	{
		x = 0;
		while (x < map->nb_col)
		{
			map->map[y][x].color = get_color_between_two(
				u->color_min, u->color_max,
				get_perc_from_val(map->map[y][x].z,
				map->deep_min, map->deep_max));
			x++;
		}
		y++;
	}
}

int			parse_row(t_map *map, char *line, int i_row)
{
	char	**lst;
	int		i;

	if (!(map->map[i_row] = (t_point*)malloc(sizeof(t_point) * map->nb_col)) ||
		!(lst = ft_strsplit(line, ' ')))
		return (0);
	i = -1;
	while (lst && lst[++i] && i < map->nb_col)
	{
		map->map[i_row][i] = (t_point){(double)i, (double)i_row,
			(double)ft_atoi(lst[i]), 0xFFFFFF};
		ft_strdel(&(lst[i]));
		map->deep_max < map->map[i_row][i].z ?
			map->deep_max = map->map[i_row][i].z : 0;
		map->deep_min > map->map[i_row][i].z ?
			map->deep_min = map->map[i_row][i].z : 0;
	}
	if (lst)
		free(lst);
	if (i != map->nb_col)
	{
		free(map->map[i_row]);
		return (0);
	}
	return (1);
}

int			parse_map_line(t_map *map, int fd, int count, char *line)
{
	int			i;

	if (map->nb_col == 0)
	{
		i = 0;
		while (line[i])
			if (line[i++] == ' ' && ++map->nb_col)
				while (line[i] == ' ')
					i++;
	}
	if (parse_map_rec(map, fd, count + 1))
	{
		if (!parse_row(map, line, count))
			return (-1);
		ft_strdel(&line);
		if (map->map[count])
			return (1);
	}
	return (0);
}

int			parse_map_rec(t_map *map, int fd, int count)
{
	char		*line;
	int			res;

	res = get_next_line(fd, &line);
	if (res == 1)
		return (parse_map_line(map, fd, count, line));
	else
	{
		if (!(map->map = (t_point**)malloc(sizeof(t_point*) * count)))
			return (-1);
		map->nb_row = count;
		return (1);
	}
}

int			parse_data(t_fdf *u, int fd)
{
	u->map->nb_col = 0;
	u->map->nb_row = 0;
	u->map->deep_max = 0;
	u->map->deep_min = 0;
	if ((parse_map_rec(u->map, fd, 0)) < 0)
		return (0);
	init_map_color(u);
	return (1);
}
