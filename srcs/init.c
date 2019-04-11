/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 01:27:56 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/25 01:27:58 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 			init_imgs(t_fdf *u)
{
	if (!(u->m_img = (t_image*)malloc(sizeof(t_image))) ||
		!(u->s_img = (t_image*)malloc(sizeof(t_image))))
		return (0);

	u->m_img->nb_row = FRAME_MAP_SIZE;
	u->m_img->nb_col = FRAME_MAP_SIZE;
	u->m_img->col0 = 0;
    new_image(u->mlx_ptr, u->m_img);

	u->s_img->nb_row = FRAME_MAP_SIZE;
	u->s_img->nb_col = FRAME_STAT_SIZE;
	u->s_img->col0 = FRAME_MAP_SIZE;
    new_image(u->mlx_ptr, u->s_img);
	return (1);
}

int 			init_mlx(t_fdf *u)
{
	u->mlx_ptr = mlx_init();
	u->win_ptr = mlx_new_window(
		u->mlx_ptr,
		FRAME_MAP_SIZE + FRAME_STAT_SIZE,
		FRAME_MAP_SIZE,
		u->filename
	);

	if (!(init_imgs(u)))
		return (0);

	mlx_hook(u->win_ptr, KP, 0, &handle_key_press, u);
	mlx_hook(u->win_ptr, KEYRELEASE, 0, &handle_key_release, u);
	mlx_hook(u->win_ptr, BUTTONPRESS, 0, &handle_button_press, u);
	mlx_hook(u->win_ptr, BUTTONRELEASE, 0, &handle_button_release, u);
	mlx_hook(u->win_ptr, MOTIONNOTIFY, 0, &handle_mouse_move, u);

	return (1);
}


int     init_fdf(t_fdf	*u)
{
	
	if (!(u->map = (t_map*)malloc(sizeof(t_map))))
		return (0);
	if (!(init_mlx(u)))
		return (0);

	u->cur_view = 1;
	u->rot_speed = 200.0f;

	u->scale = 32;
	u->depth = 0.5;
	u->x = 0.5;
	u->y = 0.5;
	u->offsetx = FRAME_MAP_SIZE / 2;
	u->offsety = FRAME_MAP_SIZE / 2;

	u->h_but = 0;
	u->h_key = 0;

	u->o_x = 0;
	u->o_y = 0;
	u->t_x = 0;
	u->t_y = 0;
	
	u->color_max = PURPLE;
	u->color_min = BLUE;
	u->color_base = YELLOW;
	u->color_null = WHITE;

	return (1);

}