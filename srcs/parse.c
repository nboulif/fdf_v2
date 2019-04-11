/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 03:56:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/26 03:56:12 by nboulif          ###   ########.fr       */
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
			if (map->map[y][x].z < 0) 
			{
				map->map[y][x].color = get_color_between_two(				
					u->color_base, u->color_min,
					get_perc_from_val(map->map[y][x].z, 0, ft_abs(map->deep_min))
				);
			}
			else if (map->map[y][x].z > 0) 
			{
				map->map[y][x].color = get_color_between_two(				
					u->color_base, u->color_max,
					get_perc_from_val(map->map[y][x].z, 0, ft_abs(map->deep_max))
				);
			}
			else
				map->map[y][x].color = u->color_base;
			x++;
		}
		y++;
	}
}

static int	 parse_row(t_map *map, char *line, int i_row)
{
	char 	**lst;
	int 	i;

	if (!(map->map[i_row] = (t_point*)malloc(sizeof(t_point) * map->nb_col)))
		return (0);
	if (!(lst = ft_strsplit(line, ' ')))
		return (0);
	i = 0;
	while (lst && lst[i] && i < map->nb_col)
	{
		map->map[i_row][i] = (t_point){(double)i, (double)i_row, 0.0, 0xFFFFFF};
		map->map[i_row][i].z = (double)ft_atoi(lst[i]);
		
		ft_strdel(&(lst[i]));
		 map->deep_max < map->map[i_row][i].z ? map->deep_max = map->map[i_row][i].z:0;
		 map->deep_min > map->map[i_row][i].z ? map->deep_min = map->map[i_row][i].z:0;
		i++;
	}
	if (lst)
		free(lst);
	if (i != map->nb_col)
		return (0); // must free first
	return (1);
}

static int	parse_map_rec(t_map *map, int fd, int count)
{
	int			res;
	char 		*line;
	int 		i;

	res = get_next_line(fd, &line);
	if (res == 1)
	{
		if (map->nb_col == 0)
        {
            i = 0;
            while(line[i])
                if (line[i++] == ' ' && ++map->nb_col)
                    while (line[i] == ' ')
                        i++;
        }
		if (parse_map_rec(map, fd, count + 1) )
		{
			parse_row(map, line, count);
			ft_strdel(&line);
			if (map->map[count])
				return (1);
		}
	}
	else if (res == 0 && (map->map = (t_point**)malloc(sizeof(t_point*) * count)))
	{
		map->nb_row = count;
		return (1);
	}
	return (0);
}

int		    parse_data(t_fdf *u, int fd)
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