/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:52:58 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			open_files(t_fdf *u, int argc, char **argv)
{
	int				i;

	if (!(u->lst_file = (char**)malloc(sizeof(char*) * argc)))
		return (0);
	i = -1;
	while (++i < argc - 1)
		if (!(u->lst_file[i] = ft_strdup(argv[i + 1])))
			return (0);
	u->lst_file[i] = NULL;
	u->nb_lst_file = argc - 1;
	return (1);
}

int			main(int argc, char **argv)
{
	int				fd;
	t_fdf			*u;

	if (argc < 2)
		ft_putendl("usage : ./fdf source_file\n"
			"where source_file is a valide map.");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 1 || !(u = (t_fdf*)malloc(sizeof(t_fdf)))
			|| !(open_files(u, argc, argv)) || !(init_fdf(u, 0))
			|| !parse_data(u, fd))
			return (0);
		close(fd);
		render_map(u);
		render_stat(u);
		mlx_loop(u->mlx_ptr);
	}
	return (0);
}
