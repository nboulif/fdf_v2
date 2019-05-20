/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:53:08 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			get_perc_from_val(double val, double min, double max)
{
	if (val == min)
		return (0.0);
	if (val == max)
		return (1.0);
	return ((val - min) / (max - min));
}

double			get_val_from_perc(int min, int max, double perc)
{
	if (min == max)
		return ((double)min);
	return (((double)min + (max - min) * perc));
}

int				get_color_between_two(int c1, int c2, double perc)
{
	if (c1 == c2)
		return (c1);
	return (
		((int)get_val_from_perc((
			c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, perc)) << 16 |
		((int)get_val_from_perc((
			c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, perc)) << 8 |
		(int)get_val_from_perc(c1 & 0xFF, c2 & 0xFF, perc));
}

void			init_vector(t_vector *v, t_point *p1, t_point *p2)
{
	v->start = *p1;
	v->end = *p2;
	v->dx = (int)ft_abs((int)p2->x - (int)p1->x);
	v->sx = (int)p1->x < (int)p2->x ? 1 : -1;
	v->dy = (int)ft_abs((int)p2->y - (int)p1->y);
	v->sy = (int)p1->y < (int)p2->y ? 1 : -1;
	v->err = (v->dx > v->dy ? v->dx : -v->dy) / 2;
}

void			draw_vec(t_fdf *u, t_point p1, t_point p2, t_image *img)
{
	t_vector	v;
	double		percent;
	int			color;

	init_vector(&v, &p1, &p2);
	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
	{
		percent = (v.dx > v.dy ? get_perc_from_val(p1.x, v.start.x, v.end.x)
			: get_perc_from_val(p1.y, v.start.y, v.end.y));
		color = get_color_between_two(p1.color, p2.color, percent);
		if (img)
			image_set_pixel(img, (int)p1.x, (int)p1.y, color);
		else
			mlx_pixel_put(u->mlx_ptr, u->win_ptr, (int)p1.x, (int)p1.y, color);
		v.err2 = v.err;
		v.err2 > -v.dx ? v.err -= v.dy : 0;
		v.err2 > -v.dx ? p1.x += v.sx : 0;
		v.err2 < v.dy ? v.err += v.dx : 0;
		v.err2 < v.dy ? p1.y += v.sy : 0;
	}
}
