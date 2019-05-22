/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_choice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:45:07 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			draw_fill_choice(t_fdf *u, int cur_row, int color, int choice)
{
	int				y;
	int				xs;
	int				xe;

	y = cur_row + 1;
	while (y < cur_row + 40)
	{
		if (choice)
		{
			xs = MAP_SIZE + 1;
			xe = MAP_SIZE + (STAT_SIZE / 2);
		}
		else
		{
			xs = MAP_SIZE + (STAT_SIZE / 2);
			xe = MAP_SIZE + STAT_SIZE - 1;
		}
		while (xs < xe)
			mlx_pixel_put(u->mlx_ptr, u->win_ptr, xs++, y, color);
		y++;
	}
}

void			draw_choice_m_view_2(t_fdf *u, int cur_row, int cur_col)
{
	cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Cross") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col,
		cur_row + 50, (u->m_view == 3 ? BLACK : WHITE), "Cross");
	cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4) -
		((ft_strlen("Point") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col,
		cur_row + 50, (u->m_view == 4 ? BLACK : WHITE), "Point");
	draw_line_sep_in_stat(u, cur_row + 80, WHITE);
	draw_mid_sep_in_stat(u, cur_row + 80, WHITE, 40);
	cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Colored") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col,
		cur_row + 90, (u->m_view == 5 ? BLACK : WHITE), "Colored");
	cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4) -
		((ft_strlen("Isometric") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col,
		cur_row + 90, (u->m_view == 6 ? BLACK : WHITE), "Isometric");
	draw_line_sep_in_stat(u, cur_row + 120, WHITE);
}

void			draw_choice_m_view_1(t_fdf *u, int cur_row)
{
	int				cur_col;

	draw_name_centered(u, 170, WHITE, "Modes");
	u->m_view < 3 ? draw_fill_choice(u, cur_row, WHITE, u->m_view % 2) : 0;
	u->m_view > 2 && u->m_view < 5 ?
		draw_fill_choice(u, cur_row + 40, WHITE, u->m_view % 2) : 0;
	u->m_view > 4 ? draw_fill_choice(u, cur_row + 80, WHITE, u->m_view % 2) : 0;
	draw_line_sep_in_stat(u, cur_row, WHITE);
	draw_mid_sep_in_stat(u, cur_row, WHITE, 40);
	cur_col = MAP_SIZE + ((STAT_SIZE / 4) -
		((ft_strlen("Default 1") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10,
		(u->m_view == 1 ? BLACK : WHITE), "Default");
	cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4) -
		((ft_strlen("Default 2") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10,
		(u->m_view == 2 ? BLACK : WHITE), "Parallel");
	draw_line_sep_in_stat(u, cur_row + 40, WHITE);
	draw_mid_sep_in_stat(u, cur_row + 40, WHITE, 40);
	draw_choice_m_view_2(u, cur_row, cur_col);
}

void			draw_choice_color(t_fdf *u, int cur_row)
{
	int				cur_col;

	u->c_selected == 1 ? draw_fill_choice(u, cur_row, WHITE, 1) : 0;
	u->c_selected == 2 ? draw_fill_choice(u, cur_row, WHITE, 0) : 0;
	draw_line_sep_in_stat(u, cur_row, WHITE);
	draw_mid_sep_in_stat(u, cur_row, WHITE, 40);
	cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Min") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10,
		(u->c_selected == 1 ? BLACK : WHITE), "Min");
	cur_col = MAP_SIZE + (STAT_SIZE / 2) + ((STAT_SIZE / 4)
		- ((ft_strlen("Max") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr, cur_col, cur_row + 10,
		(u->c_selected == 2 ? BLACK : WHITE), "Max");
	draw_line_sep_in_stat(u, cur_row + 40, WHITE);
}

void			draw_choice_s_view(t_fdf *u, int cur_row)
{
	int				cur_col;

	draw_line_sep_in_stat(u, cur_row, WHITE);
	draw_mid_sep_in_stat(u, cur_row, WHITE, 40);
	cur_col = MAP_SIZE + ((STAT_SIZE / 4) - ((ft_strlen("Options") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr,
		cur_col, cur_row + 10, (u->s_view == 1 ? BLACK : WHITE), "Options");
	cur_col = MAP_SIZE + (STAT_SIZE / 2) +
		((STAT_SIZE / 4) - ((ft_strlen("Files") * 10) / 2));
	mlx_string_put(u->mlx_ptr, u->win_ptr,
		cur_col, cur_row + 10, (u->s_view == 2 ? BLACK : WHITE), "Files");
	draw_line_sep_in_stat(u, cur_row + 40, WHITE);
}
