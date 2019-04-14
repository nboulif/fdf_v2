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

int			main(int argc, char **argv)
{
	int				fd;
	t_fdf			*u;
	
	if (argc < 2)
		ft_putendl("usage : ./fdf source_file\n"
			"where source_file is a valide map.");
	else
	{
		
		if((fd = open(argv[1], O_RDONLY)) < 1)
		{
			ft_putendl("error");
			return (0);
		}
		u = (t_fdf*)malloc(sizeof(t_fdf));

		u->lst_file = (char**)malloc(sizeof(char*) * argc);
		int i = -1;
		while(++i < argc - 1)
			u->lst_file[i] = ft_strdup(argv[i + 1]);
		u->lst_file[i] = NULL;
		u->nb_lst_file = argc - 1;
		if ((!(init_fdf(u, 0))) || !parse_data(u, fd)) 
		{
			ft_putendl("error");
			return (0);
		}
		close(fd);
		
		render_map(u);
		render_stat(u);

		mlx_loop(u->mlx_ptr);



	}
	return (0);
}

