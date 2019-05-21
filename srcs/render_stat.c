/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_stat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:36:18 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				draw_palette_2(double alpha)
{
	int				color;
	double			ooo;

	ooo = ((2 * PI) / 6);
	if (alpha <= ((2 * PI) / 6))
		color = get_color_between_two(RED, 0xff00ff,
			get_perc_from_val(alpha, 0, ooo));
	else if (alpha <= ((2 * PI) / 6) * 2)
		color = get_color_between_two(0xff00ff, BLUE,
			get_perc_from_val(alpha, ooo, ooo * 2));
	else if (alpha <= ((2 * PI) / 6) * 3)
		color = get_color_between_two(BLUE, 0x00ffff,
			get_perc_from_val(alpha, ooo * 2, ooo * 3));
	else if (alpha <= ((2 * PI) / 6) * 4)
		color = get_color_between_two(0x00ffff, GREEN,
			get_perc_from_val(alpha, ooo * 3, ooo * 4));
	else if (alpha <= (2 * PI) - (((2 * PI) / 3) / 2))
		color = get_color_between_two(GREEN, 0xffff00,
			get_perc_from_val(alpha, ooo * 4, ooo * 5));
	else
		color = get_color_between_two(0xffff00, RED,
			get_perc_from_val(alpha, ooo * 5, ooo * 6));
	return (color);
}

void			draw_palette(t_fdf *u, int cur_row)
{
	double			alpha;
	int				x2;
	int				y2;
	int				color;

	alpha = 0;
	while (alpha < (2 * PI))
	{
		color = draw_palette_2(alpha);
		x2 = 146 + 123 * cos(alpha);
		y2 = 146 + 123 * sin(alpha);
		draw_vec(
			u, (t_point){146, 146, 1, WHITE}, (t_point){(int)((146 + x2) / 2),
			(int)((146 + y2) / 2), 1, color},
			u->p_img);
		draw_vec(
			u, (t_point){(int)((146 + x2) / 2),
			(int)((146 + y2) / 2), 1, color}, (t_point){x2, y2, 1, BLACK},
			u->p_img);
		alpha += 0.0001;
	}
	mlx_put_image_to_window(u->mlx_ptr, u->win_ptr,
		u->p_img->ptr, MAP_SIZE + 1, cur_row + 1);
}

void			fill_rect_in_win(t_fdf *u)
{
	int				x;
	int				y;

	y = 0;
	while (y < MAP_SIZE)
	{
		x = 0;
		while (x < STAT_SIZE)
		{
			mlx_pixel_put(u->mlx_ptr, u->win_ptr,
				MAP_SIZE + x++, y, BLACK);
		}
		y++;
	}
}

void			draw_rect_in_win(t_fdf *u, t_rectangle *rect)
{
	int				x;
	int				y;

	x = 0;
	while (rect->x + x < rect->x + rect->w)
	{
		mlx_pixel_put(u->mlx_ptr, u->win_ptr,
			rect->x + x, rect->y, rect->color);
		mlx_pixel_put(u->mlx_ptr, u->win_ptr,
			rect->x + x++, rect->y + rect->h, rect->color);
	}
	y = 0;
	while (rect->y + y < rect->y + rect->h)
	{
		mlx_pixel_put(u->mlx_ptr, u->win_ptr,
			rect->x, rect->y + y, rect->color);
		mlx_pixel_put(u->mlx_ptr, u->win_ptr,
			rect->x + rect->w, rect->y + y++, rect->color);
	}
}

void			draw_countour_stat(t_fdf *u)
{
	t_rectangle		rect;

	rect.x = MAP_SIZE;
	rect.y = 0;
	rect.w = STAT_SIZE - 1;
	rect.h = MAP_SIZE - 1;
	rect.color = WHITE;
	fill_rect_in_win(u);
	draw_rect_in_win(u, &rect);
}
