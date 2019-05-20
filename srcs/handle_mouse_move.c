/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:23:43 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			handle_mouse_move_on_map(int x, int y, t_fdf *u)
{
	if (u->h_but == 1)
	{
		u->x += (u->o_y - y) / u->rot_speed;
		u->y -= (u->o_x - x) / u->rot_speed;
	}
	else if (u->h_but == 2)
	{
		u->offsetx += (x - u->o_x);
		u->offsety += (y - u->o_y);
	}
	else if (u->h_but == 3)
	{
		u->scale += (u->o_y - y) / 10.0f + 0.5f;
		if (u->scale < 1)
			u->scale = 1;
	}
	if (u->h_but)
		render_map(u);
}

void			handle_mouse_move_on_stat(int x, int y, t_fdf *u)
{
	int		xxx;
	int		yyy;
	int		color;

	if (u->h_but == 1 && y > 400 && y < 710 && u->c_selected)
	{
		xxx = abs(MAP_SIZE + 1 - x);
		yyy = abs(410 + 1 - y);
		color = *(int *)(u->p_img->data +
			((xxx + yyy * u->p_img->nb_col) * u->p_img->bpp));
		if (u->c_selected == 1)
			u->color_min = color;
		else
			u->color_max = color;
		init_map_color(u);
		render_map(u);
	}
}

int				handle_mouse_move(int x, int y, t_fdf *u)
{
	u->o_x = u->t_x;
	u->o_y = u->t_y;
	u->t_x = x;
	u->t_y = y;
	if (u->t_x < MAP_SIZE)
		handle_mouse_move_on_map(x, y, u);
	else
		handle_mouse_move_on_stat(x, y, u);
	return (0);
}
