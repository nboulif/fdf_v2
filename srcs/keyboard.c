/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int 		handle_key_release(int key, t_fdf *u)
{
	(void)key;
	u->h_key = 0;
	return (0);

}
int 		handle_key_press(int key, t_fdf *u)
{
	// printf("pressed %d\n", key);
	if (key == ESC_KEY)
		exit(0);
	else if (key == K_KEY)
		clear_image(u->m_img);
	else if (key == V_KEY)
	{
		u->h_key = key;
		render_map(u);
	}
	else if (key == K1_KEY && u->h_key == V_KEY)
	{
		u->cur_view = 1;
		u->h_key = 0;
		render_map(u);
	}
	else if (key == K2_KEY && u->h_key == V_KEY)
	{
		u->cur_view = 2;
		u->h_key = 0;
		render_map(u);
	}
	else if (key == K3_KEY && u->h_key == V_KEY)
	{
		u->cur_view = 3;
		u->h_key = 0;
		render_map(u);
	}
	else if (key == P_KEY)
	{
		if (u->depth < 10)
		{
			u->depth += 0.1 ;
			render_map(u);
		}
	}
	else if (key == 41)
	{
		if (u->depth > 0.1)
		{
			u->depth -= 0.1;
			render_map(u);
		}
	}
	// else if (key == NK8_KEY)
	// 	draw_square_in_image(u, u->m_img, 100, 400);
	// else if (key == NK9_KEY)
	// 	draw_square_in_image(u, u->s_img, 200, 150);
	return (0);
}