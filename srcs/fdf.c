/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char *argv[])
{
	int				fd;
	t_fdf			u;

	if (argc != 2)
		ft_putendl("usage : ./fdf source_file\n"
			"where source_file is a valide map.");
	else
	{
		if((fd = open(argv[1], O_RDONLY)) < 1)
		{
			ft_putendl("error");
			return (0);
		}
		u.filename = argv[1];

		if ((!(init_fdf(&u))) || !parse_data(&u, fd)) 
		{
			ft_putendl("error");
			return (0);
		}
		// draw_contour_frame(u, u.s_img);
		render_map(&u);

		mlx_loop(u.mlx_ptr);

		close(fd);


	}
	return (0);
}

