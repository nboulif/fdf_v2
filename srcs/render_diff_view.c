/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_diff_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point			get_view_point(t_fdf *u, int y, int x)
{
	t_point			p;
	t_point			p_tmp;

	p = u->map->map[y][x];
	p.x -= (double)(u->map->nb_col - 1) / 2.0f;
	p.y -= (double)(u->map->nb_row - 1) / 2.0f;
	p.z *= u->depth;
	p.z -= (double)(u->map->deep_min + u->map->deep_max) / 2.0f;
	p_tmp = p;
	p.x = cos(u->y) * p_tmp.x + sin(u->y) * p.z;
	p.z = -sin(u->y) * p_tmp.x + cos(u->y) * p.z;
	p.y = cos(u->x) * p_tmp.y - sin(u->x) * p.z;
	p.z = sin(u->x) * p_tmp.y + cos(u->x) * p.z;
	p.x = (p.x * u->scale) + u->offsetx;
	p.y = (p.y * u->scale) + u->offsety;
	return (p);
}

void			render_map_view_point(t_fdf *u)
{
	int				x;
	int				y;

	y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{
			t_point pooo = get_view_point(u, y, x);
			image_set_pixel(u->m_img, pooo.x, pooo.y, u->map->map[y][x].color);
			x++;
		}
		y++;
	}
}

void			render_map_view_cross(t_fdf *u)
{
	int				x;
	int				y;

	y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{
			if (x + 1 < u->map->nb_col)
				draw_vec(u, get_view_point(u, y, x), get_view_point(u, y, x + 1), u->m_img);
			if (y + 1 < u->map->nb_row)
				draw_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x), u->m_img);
			if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
				draw_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x + 1), u->m_img);
			if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
				draw_vec(u, get_view_point(u, y + 1, x), get_view_point(u, y, x + 1), u->m_img);
			x++;
		}
		y++;
	}
}

void			render_map_view_default_1(t_fdf *u)
{
	int				x;
	int				y;

	y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{
			if (x + 1 < u->map->nb_col)
				draw_vec(u, get_view_point(u, y, x), get_view_point(u, y, x + 1), u->m_img);
			if (y + 1 < u->map->nb_row)
				draw_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x), u->m_img);
			x++;
		}
		y++;
	}
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
				draw_vec(u, get_view_point(u, y, x), get_view_point(u, y, x + 1), u->m_img);
			if (y + 1 < u->map->nb_row)
				draw_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x), u->m_img);
		
			if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
			{
				t_point ttt;
				t_point ttt2;
				t_point ttt3;
				ttt = get_view_point(u, y + 1, x + 1);
				ttt2 = get_view_point(u, y, x + 1);
				while(ttt2.y < ttt.y)
				{
					draw_vec(u, get_view_point(u, y, x), ttt2, u->m_img);
					ttt2.y += 1;
				}
				ttt3 = get_view_point(u, y, x + 1);
				while(ttt3.x < ttt.x)
				{
					draw_vec(u, get_view_point(u, y, x), ttt3, u->m_img);
					ttt3.x += 1;
				}
				ttt2 = get_view_point(u, y + 1, x);
				while(ttt2.y < ttt.y)
				{
					draw_vec(u, get_view_point(u, y, x), ttt2, u->m_img);
					ttt2.y += 1;
				}
				ttt3 = get_view_point(u, y + 1, x);
				while(ttt3.x < ttt.x)
				{
					draw_vec(u, get_view_point(u, y, x), ttt3, u->m_img);
					ttt3.x += 1;
				}
			} 
			x++;
		}
		y++;
	}
}
