/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:51:41 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			handle_zoom(t_fdf *u, int dir)
{
	if (dir)
	{
		if (u->depth < 10)
			u->depth += 0.1;
	}
	else if (u->depth > 0.1)
		u->depth -= 0.1;
	render_map(u);
	return (0);
}

void		handle_change_mode(t_fdf *u, int x, int y)
{
	int		v;

	v = 0;
	if (y > 200 && y < 240)
	{
		x < MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 1 ? v = 1 : 0;
		x > MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 2 ? v = 2 : 0;
	}
	else if (y > 240 && y < 280)
	{
		x < MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 3 ? v = 3 : 0;
		x > MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 4 ? v = 4 : 0;
	}
	else
	{
		x < MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 5 ? v = 5 : 0;
		x > MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 6 ? v = 6 : 0;
	}
	if (v)
	{
		u->m_view = v;
		render_stat(u);
		render_map(u);
	}
}

int			handle_button_release(int key, int x, int y, t_fdf *u)
{
	(void)x;
	(void)y;
	if (key < 4)
	{
		if (key == 1)
		{
			u->t_x = 0;
			u->t_y = 0;
		}
		if (u->c_selected && !(y > 370 && y < 400 && x > MAP_SIZE))
		{
			u->c_selected = 0;
			render_stat(u);
		}
		u->h_but = 0;
	}
	return (1);
}

int			handle_button_press(int key, int x, int y, t_fdf *u)
{
	int			old_key;

	old_key = u->h_but;
	if (key < 4)
		u->h_but = key;
	if (x < MAP_SIZE)
	{
		if (key == SCROLLUP_KEY)
			handle_zoom(u, 1);
		else if (key == SCROLLDOWN_KEY)
			handle_zoom(u, 0);
	}
	else if (key == 1)
		handle_stat_button(x, y, u);
	return (1);
}
