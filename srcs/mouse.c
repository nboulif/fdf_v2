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

int 		handle_button_press(int key, int x, int y, t_fdf *u)
{
	int 		color;

	(void)x;
	(void)y;
	printf("pressed %d\n", key);
	if (key < 4)
		u->h_but = key;
	key == BUT1_KEY ? color = RED: 0;
	key == BUT2_KEY ? color = MIDNIGHTBLUE: 0;
	key == BUT3_KEY ? color = GREEN1: 0;
	key > BUT3_KEY ? color = rand(): 0;
	if (key == SCROLLUP_KEY)
		handle_zoom(u, 1);
	else if (key == SCROLLDOWN_KEY)
		handle_zoom(u, 0);
	return (1);
}

int 		handle_button_release(int key, int x, int y, t_fdf *u)
{
	printf("release %d\n", key);
	(void)x;
	(void)y;
	if (key < 4)
	{
		if (key == 1) 
		{
			u->t_x = 0;
			u->t_y = 0;
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
		printf("ffff %d\n", (u->o_y - y));
		printf("ffff %f\n", (u->o_y - y) / 10.0f + 0.5f);
		printf("@@@@@@@@@@@@@@@@\n");
		u->scale += (u->o_y - y) / 10.0f + 0.5f;
		if (u->scale < 1)
			u->scale = 1;
	}
	if (u->h_but) 
		render_map(u);
	return (0);
}
