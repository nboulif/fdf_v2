/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_s.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 03:37:14 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/25 03:37:15 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_S_H
# define FDF_S_H

typedef struct		s_image
{
	void			*ptr;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;

	int				col0;
	int				row0;
	int				nb_row;
	int				nb_col;

}					t_image;

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;

	int				color;
}					t_point;

typedef struct		s_map
{
	t_point			**map;
	int				nb_row;
	int				nb_col;

	int				deep_max;
	int				deep_min;
}					t_map;

typedef struct		s_fdf
{
	void			*mlx_ptr;
	void			*win_ptr;

	t_image			*m_img;
	t_image			*p_img;

	t_map			*map;

	int				s_view;
	int				c_selected;
	char			**lst_file;
	int				nb_lst_file;

	int				m_view;

	double			rot_speed;

	int				scale;
	double			depth;
	double			offsetx;
	double			offsety;
	double			x;
	double			y;

	int				h_but;
	int				h_key;
	
	int				o_x;
	int				o_y;
	
	int				t_x;
	int				t_y;

	int				color_max;
	int				color_base;
	int				color_null;
	int				color_min;
	
}					t_fdf;

typedef struct		s_vector
{
	t_point			start;
	t_point			end;
	double			dx;
	double			dy;
	double			sx;
	double			sy;
	double			err;
	double			err2;
}					t_vector;

typedef struct		s_rectangle
{
	int				x;
	int				y;
	int				h;
	int				w;
	int				color;
}					t_rectangle;

#endif