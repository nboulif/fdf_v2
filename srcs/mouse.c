/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			handle_zoom(t_fdf *u, int dir)
{
	if (dir)
	{
		if (u->depth < 10)
			u->depth += 0.1 ;
	}
	else if (u->depth > 0.1)
			u->depth -= 0.1;
	render_map(u);
	return (0);
}

void		handle_change_mode(t_fdf *u, int x, int y)
{
	int v;

	v = 0;

	if (y > 200 && y < 240)
	{
		x < MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 1 ? v = 1 : 0 ;
		x > MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 2 ? v = 2 : 0 ;
	}
	else if (y > 240 && y < 280)
	{
		x < MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 3 ? v = 3 : 0 ;
		x > MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 4 ? v = 4 : 0 ;
	}
	else
	{
		x < MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 5 ? v = 5 : 0 ;
		x > MAP_SIZE + PALETTE_SIZE / 2 && u->m_view != 6 ? v = 6 : 0 ;
	}

	if (v)
	{
		u->m_view = v;
		mlx_put_image_to_window(u->mlx_ptr, u->win_ptr, u->s_img->ptr, MAP_SIZE, 0);
		render_stat(u);
		render_map(u);
	}
	
	
}

int 		handle_button_press(int key, int x, int y, t_fdf *u)
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
	else
	{
		if (u->s_view == 1)
		{		
			if (y > 370 && y < 400)
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
			if (u->h_but == 1 && y > 400 && y < 710 && u->c_selected)
			{

				int xxx;
				int yyy;

				xxx = abs(MAP_SIZE + 1 - x);
				yyy = abs(410 + 1 - y);
				int color =  *(int *)(u->p_img->data + ((xxx + yyy * u->p_img->nb_col) * u->p_img->bpp));
				if(u->c_selected == 1)
					u->color_min = color;
				else
					u->color_max = color;
				init_map_color(u);
				render_map(u);
				// render_stat(u);
			}

			if (y > 50 && y < 90)
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
			else if (y > 200 && y < 320)
			{
				handle_change_mode(u, x, y);
			}

		
		}
		else
		{
			if (y > 110)
			{
				int o;

				o = (y - 110) / 40;
				if (o <= u->nb_lst_file)
				{
					reinit(u, u->lst_file[o]);
				}

			}
		}
			
		
	}
	return (1);
}

int 		handle_button_release(int key, int x, int y, t_fdf *u)
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

int 		handle_mouse_move(int x, int y, t_fdf *u)
{	
	u->o_x = u->t_x;
	u->o_y = u->t_y;
	u->t_x = x;
	u->t_y = y;
	if (u->t_x < MAP_SIZE)
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
	else
	{
		if (u->h_but == 1 && y > 400 && y < 710 && u->c_selected)
		{

			int xxx;
			int yyy;

			xxx = abs(MAP_SIZE + 1 - x);
			yyy = abs(410 + 1 - y);
			int color =  *(int *)(u->p_img->data + ((xxx + yyy * u->p_img->nb_col) * u->p_img->bpp));
			if(u->c_selected == 1)
				u->color_min = color;
			else
				u->color_max = color;
			init_map_color(u);
			render_map(u);
			// render_stat(u);
		}
	}
	return (0);
}
