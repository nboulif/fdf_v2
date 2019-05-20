/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stat_button.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		select_file(int y, t_fdf *u)
{
	int o;
	
	if (y > 110)
	{
		o = (y - 110) / 40;
		if (o <= u->nb_lst_file)
			reinit(u, u->lst_file[o]);
	}
}

void		handle_select_stat_view(int x, t_fdf *u)
{
	if (x < MAP_SIZE + (STAT_SIZE / 2))
	{
		if (u->s_view == 2)
		{
			u->s_view = 1;
			render_stat(u);
		}
	}
	else if (u->s_view == 1)
	{
		u->s_view = 2;
		render_stat(u);
	}
}

void		handle_change_min_max_color(int x, int y, t_fdf *u)
{
	int			xxx;
	int			yyy;
	int			color;

	xxx = abs(MAP_SIZE + 1 - x);
	yyy = abs(410 + 1 - y);
	color =  *(int *)(u->p_img->data + ((xxx + yyy * u->p_img->nb_col) * u->p_img->bpp));
	if(u->c_selected == 1)
		u->color_min = color;
	else
		u->color_max = color;
	init_map_color(u);
	render_map(u);
}

void		handle_select_min_max_button(int x, t_fdf *u)
{
	if (x < MAP_SIZE + (STAT_SIZE / 2))
	{
		if (u->c_selected != 1)
			{
				u->c_selected = 1;
				render_stat(u);
			}
	}
	else if (u->c_selected != 2)
	{
		u->c_selected = 2;
		render_stat(u);
	}	
}

void		handle_stat_button(int x, int y, t_fdf *u)
{
	if (u->s_view == 1)
	{		
		if (y > 370 && y < 400)
			handle_select_min_max_button(x, u);
		if (u->h_but == 1 && y > 400 && y < 710 && u->c_selected)
				handle_change_min_max_color(x, y, u);
		if (y > 50 && y < 90)
			handle_select_stat_view(x, u);
		else if (y > 200 && y < 320)
			handle_change_mode(u, x, y);
	}
	else
		select_file(y, u);
}