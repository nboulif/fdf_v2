/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			draw_boxed_text(t_fdf *u, char *str, int color, t_point *p)
{
	t_rectangle		rect;

	rect.x = p->x;
	rect.y = p->y;
	rect.w = 10 * ft_strlen(str) + 20;
	rect.h = 30 ;
	rect.color = p->color;
	draw_rect_in_win(u, &rect);
		
	mlx_string_put(u->mlx_ptr, u->win_ptr, rect.x + 10, rect.y + 5,
		color, str);
}

void			draw_mid_sep_in_stat(t_fdf *u, int cur_row, int color, int h)
{
	int				x;
	int				y;

	y = cur_row;
	x = MAP_SIZE + (STAT_SIZE / 2);
	while (y < cur_row + h)
		mlx_pixel_put(u->mlx_ptr, u->win_ptr, x, y++, color);
}

void			draw_line_sep_in_stat(t_fdf *u, int cur_row, int color)
{
	int				x;

	x = MAP_SIZE;
	while (x < MAP_SIZE + STAT_SIZE)
		mlx_pixel_put(u->mlx_ptr, u->win_ptr, x++, cur_row, color);
}

void			draw_name_centered(t_fdf *u, int cur_row, int color, char *str)
{
	int				x;

	x = MAP_SIZE + ((STAT_SIZE / 2) - ((ft_strlen(str) * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, x, cur_row, color, str);
}