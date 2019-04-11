/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void        init_vector(t_vector *v, t_point *p1, t_point *p2)
{
	v->start = *p1;
	v->end = *p2;
	v->dx = (int)ft_abs((int)p2->x - (int)p1->x);
	v->sx = (int)p1->x < (int)p2->x ? 1 : -1;
	v->dy = (int)ft_abs((int)p2->y - (int)p1->y);
	v->sy = (int)p1->y < (int)p2->y ? 1 : -1;
	v->err = (v->dx > v->dy ? v->dx : -v->dy) / 2;
}

void		trace_vec(t_fdf *u, t_point p1, t_point p2)
{
	t_vector	v;
	double	percent;

    init_vector(&v, &p1, &p2);
	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
    {
        percent = (v.dx > v.dy ? get_perc_from_val(p1.x, v.start.x, v.end.x)
            : get_perc_from_val(p1.y, v.start.y, v.end.y));
        image_set_pixel(u->m_img, (int)p1.x, (int)p1.y, get_color_between_two(p1.color,
                p2.color, percent));
        v.err2 = v.err;
        v.err2 > -v.dx ? v.err -= v.dy : 0 ;
        v.err2 > -v.dx ? p1.x += v.sx : 0 ;
        v.err2 < v.dy ? v.err += v.dx : 0 ;
        v.err2 < v.dy ? p1.y += v.sy : 0 ;
    }
}

t_point	get_view_point(t_fdf *u, int y, int x)
{
    t_point     p;
    t_point	    p_tmp;

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

void		render_map(t_fdf *u)
{
	int			x;
	int			y;
	t_map		*map;

	map = u->map;
	clear_image(u->m_img);
	y = 0;
	while (y < map->nb_row)
	{
		x = 0;
		while (x < map->nb_col)
		{
            if (x + 1 < map->nb_col)
                    trace_vec(u, get_view_point(u, y, x), get_view_point(u, y, x + 1));
            if (y + 1 < map->nb_row)
                trace_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x));
            
            if (u->cur_view == 2)
            {
                if (y + 1 < map->nb_row && x + 1 < map->nb_col)
                    trace_vec(u, get_view_point(u, y, x), get_view_point(u, y + 1, x + 1));
                if (y + 1 < map->nb_row && x + 1 < map->nb_col)
                    trace_vec(u, get_view_point(u, y + 1, x), get_view_point(u, y, x + 1));
            }
            else if (u->cur_view == 3)
            {
                if (y + 1 < map->nb_row && x + 1 < map->nb_col)
                {
                    t_point ttt;
                    t_point ttt2;
                    t_point ttt3;

                    ttt = get_view_point(u, y + 1, x + 1);
                    ttt2 = get_view_point(u, y, x + 1);
                    while(ttt2.y < ttt.y)
                    {
                        trace_vec(u, get_view_point(u, y, x), ttt2);
                        ttt2.y += 1;
                    }
                    ttt3 = get_view_point(u, y, x + 1);
                    while(ttt3.x < ttt.x)
                    {
                        trace_vec(u, get_view_point(u, y, x), ttt3);
                        ttt3.x += 1;
                    }
                    ttt2 = get_view_point(u, y + 1, x);
                    while(ttt2.y < ttt.y)
                    {
                        trace_vec(u, get_view_point(u, y, x), ttt2);
                        ttt2.y += 1;
                    }
                    ttt3 = get_view_point(u, y + 1, x);
                    while(ttt3.x < ttt.x)
                    {
                        trace_vec(u, get_view_point(u, y, x), ttt3);
                        ttt3.x += 1;
                    }
                }                
            }
			
            x++;
		}
		y++;
	}
	mlx_put_image_to_window(u->mlx_ptr, u->win_ptr, u->m_img->ptr, 0, 0);
}