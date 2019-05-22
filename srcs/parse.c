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

int			parse_row_check(t_map *map, char **lst, int i_row, int i)
{
	int j;

	j = 0;
	if (!(ft_isdigit(lst[i][j]) || lst[i][j] == '-'))
	{
		ft_strdel(&(lst[i]));
		return (0);
	}
	while (lst[i][++j])
	{
		if (!ft_isdigit(lst[i][j]))
		{
			ft_strdel(&(lst[i]));
			return (0);
		}
	}
	map->map[i_row][i] = (t_point){(double)i, (double)i_row,
		(double)ft_atoi(lst[i]), 0xFFFFFF};
	ft_strdel(&(lst[i]));
	map->deep_max < map->map[i_row][i].z ?
		map->deep_max = map->map[i_row][i].z : 0;
	map->deep_min > map->map[i_row][i].z ?
		map->deep_min = map->map[i_row][i].z : 0;
	return (1);
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
		if (!parse_row_check(map, lst, i_row, i))
			return (0);
	if (lst)
		free(lst);
	if (i != map->nb_col)
	{
		free(map->map[i_row]);
		return (0);
	}
	return (1);
}

int			parse_map_line(t_map *map, char *line)
{
	int			i;
	int			o;

	o = 0;
	i = 0;
	while (line[i])
		if (line[i++] == ' ' && ++o)
			while (line[i] == ' ')
				i++;
	if (!o)
		return (0);
	if (map->nb_col == 0)
		map->nb_col = o;
	else if (map->nb_col != o)
		return (0);
	return (1);
}

int			parse_map_rec(t_map *map, int fd, int count)
{
	char		*line;
	int			res;

	res = get_next_line(fd, &line);
	if (res == 1)
	{
		if (parse_map_line(map, line) && parse_map_rec(map, fd, count + 1))
		{
			res = parse_row(map, line, count);
			ft_strdel(&line);
			if (!res)
				return (0);
			if (map->map[count])
				return (1);
		}
	}
	else if (res == 0)
	{
		if (!count || !(map->map = (t_point**)malloc(sizeof(t_point*) * count)))
			return (0);
		map->nb_row = count;
		return (1);
	}
	return (0);
}

int			parse_data(t_fdf *u, int fd)
{
	u->map->nb_col = 0;
	u->map->nb_row = 0;
	u->map->deep_max = 0;
	u->map->deep_min = 0;
	if (!(parse_map_rec(u->map, fd, 0)))
		return (0);
	init_map_color(u);
	return (1);
}
