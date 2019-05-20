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

void			reinit(t_fdf *u, char *str)
{
	int				fd;

	if((fd = open(str, O_RDONLY)) < 1)
	{
		ft_putendl("errorrrrr");
		exit(0);
	}
	if ((!(init_fdf(u, 1))) || !parse_data(u, fd)) 
	{
		ft_putendl("errorrrr");
		exit (0);
	}
	close(fd);
	render_map(u);
	render_stat(u);
}

void			render_stat(t_fdf *u)
{
	int				i;
	int				j;

	draw_countour_stat(u);
	draw_name_centered(u, 10, WHITE, "FDF by nboulif");
	draw_fill_choice(u, 50, WHITE, u->s_view % 2);
	draw_choice_s_view(u, 50);
	if (u->s_view == 1)
	{
		draw_line_sep_in_stat(u, 160, WHITE);
		draw_name_centered(u, 170, WHITE, "Modes");
		draw_choice_m_view(u, 200);
		draw_name_centered(u, 330, WHITE, "Colors");
		draw_choice_color(u, 360);
		draw_palette(u, 410);
	}
	else if (u->s_view == 2)
	{
		i = 0;
		j = 100;
		while(u->lst_file[i])
		{
			draw_name_centered(u, j, WHITE, u->lst_file[i++]);
			j += 40;
		}
	}
}

void			render_map(t_fdf *u)
{
	clear_image(u->m_img);
	if (u->m_view == 1)
		render_map_view_default_1(u);
	else if (u->m_view == 3)
		render_map_view_cross(u);
	else if (u->m_view == 4)
		render_map_view_point(u);
	else if (u->m_view == 5)
		render_map_view_colored(u);
	mlx_put_image_to_window(u->mlx_ptr, u->win_ptr, u->m_img->ptr, 0, 0);
}
