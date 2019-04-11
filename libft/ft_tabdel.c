/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:11:15 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/27 21:11:17 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(char ***tab)
{
	size_t n;

	n = 0;
	while (*tab && (*tab)[n])
		ft_strdel(*(tab) + n++);
	ft_memdel((void**)(tab));
}
