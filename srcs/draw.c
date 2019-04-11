/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/24 19:54:28 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_perc_from_val(double val, double min, double max)
{
	if (val == min)
		return (0.0);
	if (val == max)
		return (1.0);
	return ((val - min) / (max - min));
}

double		get_val_from_perc(int min, int max, double perc)
{
	if (min == max)
		return ((double)min);
	return (((double)min + (max - min) * perc));
}

int			get_color_between_two(int c1, int c2, double perc)
{
	if (c1 == c2)
		return (c1);
	return (
        ((int)get_val_from_perc((
            c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, perc)) << 16 |
        ((int)get_val_from_perc((
            c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, perc)) << 8 |
	    (int)get_val_from_perc(c1 & 0xFF, c2 & 0xFF, perc)
    );
}
