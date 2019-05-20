/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:54:15 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/20 18:59:21 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		image_set_pixel(t_image *image, int x, int y, int color)
{
	if (x < 0 || x >= image->nb_col || y < 0 || y >= image->nb_row)
		;
	else
		*(int *)(image->data + ((x + y * image->nb_col) * image->bpp)) = color;
}

void		clear_image(t_image *image)
{
	ft_bzero(image->data, image->nb_col * image->nb_row * image->bpp);
}

void		del_image(void *mlx_ptr, t_image *img)
{
	if (img->ptr != NULL)
		mlx_destroy_image(mlx_ptr, img->ptr);
	ft_memdel((void **)&img);
}

int			new_image(void *mlx_ptr, t_image *img)
{
	img->ptr = mlx_new_image(mlx_ptr, img->nb_col, img->nb_row);
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->sizeline,
		&img->endian);
	img->bpp /= 8;
	return (1);
}
