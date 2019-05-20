/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:51:47 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			handle_key_release(int key, t_fdf *u)
{
	(void)key;
	u->h_key = 0;
	return (0);
}

void		handle_key_press_2(int key, t_fdf *u)
{
	if (key == P_KEY && u->depth < 10)
		u->depth += 0.1;
	else if (key == 41 && u->depth > 0.1)
		u->depth -= 0.1;
	else if (key == T_KEY && u->rot_speed > 20.0f)
		u->rot_speed -= 20.0f;
	else if (key == R_KEY && u->rot_speed < 500.0f)
		u->rot_speed += 20.0f;
	else if (key == H_KEY)
	{
		u->scale += -10 / 10.0f + 0.5f;
		if (u->scale < 1)
			u->scale = 1;
	}
	else if (key == J_KEY)
	{
		u->scale += 10 / 10.0f + 0.5f;
		if (u->scale < 1)
			u->scale = 1;
	}
}

int			handle_key_press(int key, t_fdf *u)
{
	if (key == ESC_KEY)
		exit(0);
	else if (key == K_KEY)
		clear_image(u->m_img);
	else if (key == V_KEY)
		u->h_key = key;
	else if (u->h_key == V_KEY)
	{
		if (key == K1_KEY)
			u->m_view = 1;
		else if (key == K2_KEY)
			u->m_view = 2;
		else if (key == K3_KEY)
			u->m_view = 3;
		u->h_key = 0;
	}
	else
		handle_key_press_2(key, u);
	render_map(u);
	return (0);
}
