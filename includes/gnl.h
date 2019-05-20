/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:46 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 17:43:34 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <limits.h>

# define BUFF_SIZE 100000

typedef struct		s_gnl_utils
{
	char			buf[BUFF_SIZE + 1];
	char			*r[OPEN_MAX];
	int				ret;
	int				len;
	int				n;
}					t_gnl_utils;

int					get_next_line(const int fd, char **line);

#endif
