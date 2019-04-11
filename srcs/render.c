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


t_point	rotate(t_point p_o, t_fdf *u)
{
	t_point	    p_f;
	double		x;
	double		y;
	double		z;

	x = p_o.x;
	z = p_o.z;
	p_f.x = cos(u->y) * x + sin(u->y) * z;
	p_f.z = -sin(u->y) * x + cos(u->y) * z;
	y = p_o.y;
	z = p_f.z;
	p_f.y = cos(u->x) * y - sin(u->x) * z;
	p_f.z = sin(u->x) * y + cos(u->x) * z;
	p_f.color = p_o.color;
	return (p_f);
}

int			line_process_point(t_fdf *u, t_vector *v, t_point *p1,
		t_point *p2)
{
	double	percent;

	// if (p1->x < 0 || p1->x >= FRAME_MAP_SIZE || p1->y < 0 || p1->y >= FRAME_MAP_SIZE
	// 	|| p2->x < 0 || p2->x >= FRAME_MAP_SIZE || p2->y < 0 || p2->y >= FRAME_MAP_SIZE)
	// 	return (1);
	percent = (v->dx > v->dy ?
			get_perc_from_val((int)p1->x, (int)v->start.x, (int)v->end.x)
			: get_perc_from_val((int)p1->y, (int)v->start.y, (int)v->end.y));
	image_set_pixel(u->m_img, (int)p1->x, (int)p1->y, get_color_between_two(p1->color,
				p2->color, percent));
	v->err2 = v->err;
	if (v->err2 > -v->dx)
	{
		v->err -= v->dy;
		p1->x += v->sx;
	}
	if (v->err2 < v->dy)
	{
		v->err += v->dx;
		p1->y += v->sy;
	}
	return (0);
}

void		line(t_fdf *u, t_point p1, t_point p2)
{
	t_vector	v;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	v.start = p1;
	v.end = p2;
	// if (!lineclip(&p1, &p2))
	// 	return ;
	v.dx = (int)ft_abs((int)p2.x - (int)p1.x);
	v.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	v.dy = (int)ft_abs((int)p2.y - (int)p1.y);
	v.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	v.err = (v.dx > v.dy ? v.dx : -v.dy) / 2;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
		if (line_process_point(u, &v, &p1, &p2))
			break ;
}

t_point	get_view_point(t_fdf *u, int y, int x)
{
    t_point     p;

    p = u->map->map[y][x];
	p.x -= (double)(u->map->nb_col - 1) / 2.0f;
	p.y -= (double)(u->map->nb_row - 1) / 2.0f;
	p.z *= u->depth;
	p.z -= (double)(u->map->deep_min + u->map->deep_max) / 2.0f;
	p = rotate(p, u);
	p.x *= u->scale;
	p.y *= u->scale;
	p.x += u->offsetx;
	p.y += u->offsety;
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
                    line(u, get_view_point(u, y, x), get_view_point(u, y, x + 1));
            if (y + 1 < map->nb_row)
                line(u, get_view_point(u, y, x), get_view_point(u, y + 1, x));
            
            if (u->cur_view == 2)
            {
                if (y + 1 < map->nb_row && x + 1 < map->nb_col)
                    line(u, get_view_point(u, y, x), get_view_point(u, y + 1, x + 1));
                if (y + 1 < map->nb_row && x + 1 < map->nb_col)
                    line(u, get_view_point(u, y + 1, x), get_view_point(u, y, x + 1));
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
                        line(u, get_view_point(u, y, x), ttt2);
                        ttt2.y += 1;
                    }
                    ttt3 = get_view_point(u, y, x + 1);
                    while(ttt3.x < ttt.x)
                    {
                        line(u, get_view_point(u, y, x), ttt3);
                        ttt3.x += 1;
                    }
                    ttt2 = get_view_point(u, y + 1, x);
                    while(ttt2.y < ttt.y)
                    {
                        line(u, get_view_point(u, y, x), ttt2);
                        ttt2.y += 1;
                    }
                    ttt3 = get_view_point(u, y + 1, x);
                    while(ttt3.x < ttt.x)
                    {
                        line(u, get_view_point(u, y, x), ttt3);
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