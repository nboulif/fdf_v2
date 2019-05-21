/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_diff_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:19:07 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// t_point        rasterise_iso(t_fdf *fdf, t_point p, int z)
// {
//     double cte1;
//     double cte2;

//     cte1 = 0.5;
//     cte2 = 0.5;
//     fdf->zoom = fdf->zoom < 0 ? 0 : fdf->zoom;
//     p.x = fdf->xoffset + (p.x * fdf->zoom);
//     p.y = fdf->yoffset + (p.y * fdf->zoom);
//     z = z * fdf->altitude;
//     if (z > 0)
//         p.color = fdf->color2;
//     else
//         p.color = fdf->color1;
//     p.x = fdf->xoffset + (cte1 * p.x - cte2 * p.y);
//     p.y = fdf->yoffset + (-z + (cte1 / 2.0) * p.x + (cte2 / 2.0) * p.y);
//     p.border = 0;
//     return (p);
// }

// t_point        rasterise_par(t_fdf *fdf, t_point p, int z)
// {
//     double cte;

//     cte = 0.5;
//     fdf->zoom = fdf->zoom < 0 ? 0 : fdf->zoom;
//     p.x = fdf->xoffset + (p.x * fdf->zoom);
//     p.y = fdf->yoffset + (p.y * fdf->zoom);
//     z = z * fdf->altitude;
//     if (z > 0)
//         p.color = fdf->color2;
//     else
//         p.color = fdf->color1;
//     p.x = p.x + cte * z;
//     p.y = p.y + (cte / 2.0) * z;
//     p.border = 0;
//     return (p);
// }

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

	// p.x = cos(u->y) * p_tmp.x + sin(u->y) * p.z;
	// p.z = -sin(u->y) * p_tmp.x + cos(u->y) * p.z;
	// p.y = cos(u->x) * p_tmp.y - sin(u->x) * p.z;
	// p.z = sin(u->x) * p_tmp.y + cos(u->x) * p.z;


	p.x = (p.x * u->scale) + u->offsetx;
	p.y = (p.y * u->scale) + u->offsety;

	// p.x = p.x + 0.5 * p.z;
	// p.y = p.y + (0.5 / 2.0f) * p.z;

    p.x = (0.5 * p.x - 0.5 * p.y);
    p.y = (-p.z + (0.5 / 2.0) * p.x + (0.5 / 2.0) * p.y);

	return (p);
}

void			render_map_view_point(t_fdf *u)
{
	int				x;
	int				y;
	t_point			p;

	y = 0;
	while (y < u->map->nb_row)
	{
		x = 0;
		while (x < u->map->nb_col)
		{
			p = get_view_point(u, y, x);
			image_set_pixel(u->m_img, p.x, p.y, u->map->map[y][x].color);
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
				draw_vec(u, get_view_point(u, y, x),
					get_view_point(u, y, x + 1), u->m_img);
			if (y + 1 < u->map->nb_row)
				draw_vec(u, get_view_point(u, y, x),
					get_view_point(u, y + 1, x), u->m_img);
			if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
				draw_vec(u, get_view_point(u, y, x),
					get_view_point(u, y + 1, x + 1), u->m_img);
			if (y + 1 < u->map->nb_row && x + 1 < u->map->nb_col)
				draw_vec(u, get_view_point(u, y + 1, x),
					get_view_point(u, y, x + 1), u->m_img);
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
				draw_vec(u, get_view_point(u, y, x),
					get_view_point(u, y, x + 1), u->m_img);
			if (y + 1 < u->map->nb_row)
				draw_vec(u, get_view_point(u, y, x),
					get_view_point(u, y + 1, x), u->m_img);
			x++;
		}
		y++;
	}
}
