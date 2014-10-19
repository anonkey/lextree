/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 19:59:24 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/19 20:00:29 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(void ***tab)
{
	int		i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i])
	{
		ft_memdel(&((*tab)[i]));
		++i;
	}
	ft_memdel((void **)tab);
}
