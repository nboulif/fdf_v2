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
	// WINDOW
	char			*filename;

	void			*mlx_ptr;
	void			*win_ptr;

	t_image			*m_img; // map frame
	t_image			*s_img; // stat frame

	t_map			*map;

	// VIEW
	int				cur_view;

	int				scale;
	double			depth;
	double			offsetx;
	double			offsety;
	double			x;
	double			y;

	// EVENT
	int				h_but; //hang_button
	int				h_key; //hang_key
	
	int				o_x;
	int				o_y;
	
	int				t_x;
	int				t_y;

	// COLOR
	int				color_max;
	int				color_base;
	int				color_null;
	int				color_min;
	
}					t_fdf;

typedef struct		s_vector
{
	t_point	start;
	t_point	end;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}					t_vector;
#endif