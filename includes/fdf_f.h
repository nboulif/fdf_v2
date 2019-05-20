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

int					init_fdf(t_fdf	*u, int reinit);
void				reinit(t_fdf *u, char *str);

int					parse_data(t_fdf  *u, int fd);
void				init_map_color(t_fdf *u);

void				image_set_pixel(t_image *image, int x, int y, int color);
void				clear_image(t_image *image);
void				del_image(void* mlx_ptr, t_image *img);
int					new_image(void* mlx_ptr, t_image *img);

int					handle_key_press(int key, t_fdf *u);
int					handle_key_release(int key, t_fdf *u);

int					handle_zoom(t_fdf *u, int dir);
int					handle_button_press(int key, int x, int y, t_fdf *u);
int					handle_button_release(int key, int x, int y, t_fdf *u);
int					handle_mouse_move(int x, int y, t_fdf *u);
void				handle_stat_button(int x, int y, t_fdf *u);
void				handle_change_mode(t_fdf *u, int x, int y);

double				get_perc_from_val(double val, double min, double max);
double				get_val_from_perc(int min, int max, double perc);
int					get_color_between_two(int c1, int c2, double perc);

void				draw_vec(t_fdf *u, t_point p1, t_point p2, t_image *img);
void				init_vector(t_vector *v, t_point *p1, t_point *p2);

void				draw_palette(t_fdf *u, int cur_row);
void				draw_fill_choice(t_fdf *u, int cur_row, int color, int choice);

void				draw_fill_choice(t_fdf *u, int cur_row, int color, int choice);
void				draw_choice_m_view(t_fdf *u, int cur_row);
void				draw_choice_color(t_fdf *u, int cur_row);
void				draw_choice_s_view(t_fdf *u, int cur_row);

void				draw_boxed_text(t_fdf *u, char *str, int color, t_point *p);
void				draw_mid_sep_in_stat(t_fdf *u, int cur_row, int color, int h);
void				draw_line_sep_in_stat(t_fdf *u, int cur_row, int color);
void				draw_name_centered(t_fdf *u, int cur_row, int color, char *str);

void				render_map(t_fdf *u);
void				render_stat(t_fdf *u);

void				render_map_view_point(t_fdf *u);
void				render_map_view_cross(t_fdf *u);
void				render_map_view_default_1(t_fdf *u);
void				render_map_view_colored(t_fdf *u);

void				draw_palette(t_fdf *u, int cur_row);
void				draw_rect_in_win(t_fdf *u, t_rectangle *rect);
void				draw_countour_stat(t_fdf *u);

#endif