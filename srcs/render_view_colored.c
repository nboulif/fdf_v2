/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view_colored.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:36:34 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			render_map_view_colored_2(t_fdf *u, int x, int y)
{
	t_point ttt;
	t_point ttt2;
	t_point ttt3;

	ttt = get_view_point(u, y + 1, x + 1);
	ttt2 = get_view_point(u, y, x + 1);
	ttt2.y--;
	while (ttt2.y++ < ttt.y)
		draw_vec(u, get_view_point(u, y, x), ttt2, u->m_img);
	ttt3 = get_view_point(u, y, x + 1);
	ttt3.x--;
	while (ttt3.x++ < ttt.x)
		draw_vec(u, get_view_point(u, y, x), ttt3, u->m_img);
	ttt2 = get_view_point(u, y + 1, x);
	ttt2.y--;
	while (ttt2.y++ < ttt.y)
		draw_vec(u, get_view_point(u, y, x), ttt2, u->m_img);
	ttt3 = get_view_point(u, y + 1, x);
	ttt3.x--;
	while (ttt3.x++ < ttt.x)
		draw_vec(u, get_view_point(u, y, x), ttt3, u->m_img);
}

void			render_map_view_colored(t_fdf *u)
{
	int			x;
	int			y;

	y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{
			if (x + 1 < u->map->nb_col)
				draw_vec(u, get_view_point(u, y, x),
					get_view_point(u, y, x + 1), u->m_img);
			if (y + 1 < u->map->nb_row)
				draw_vec(u, get_view_point(u, y, x),
					get_view_point(u, y + 1, x), u->m_img);
			if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
				render_map_view_colored_2(u, x, y);
			x++;
		}
		y++;
	}
}
