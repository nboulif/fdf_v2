/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_f.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 03:37:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/25 03:37:24 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_F_H
# define FDF_F_H

int                 init_fdf(t_fdf	*u);

int		            parse_data(t_fdf  *u, int fd);

void		        image_set_pixel(t_image *image, int x, int y, int color);
void		        clear_image(t_image *image);
void		        del_image(void* mlx_ptr, t_image *img);
int			        new_image(void* mlx_ptr, t_image *img);

int 		        handle_key_press(int key, t_fdf *u);
int 		        handle_key_release(int key, t_fdf *u);

int			        handle_zoom(t_fdf *u, int dir);
int 		        handle_button_press(int key, int x, int y, t_fdf *u);
int 		        handle_button_release(int key, int x, int y, t_fdf *u);
int 		        handle_mouse_move(int x, int y, t_fdf *u);

void		        render_map(t_fdf *u);

double	            get_perc_from_val(double val, double min, double max);
double		        get_val_from_perc(int min, int max, double perc);
int			        get_color_between_two(int c1, int c2, double perc);
void		        trace_vec(t_fdf *u, t_point p1, t_point p2);

#endif