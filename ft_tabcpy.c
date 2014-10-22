/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 19:49:10 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/22 22:06:02 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_tab.h"

void	*ft_tabcpy(void *tab, int addsize, size_t celllen)
{
	size_t		len;
	void	*newtab;
	char	buffer[MAX_CELL_LEN];

	ft_bzero(buffer, celllen);
	len = 0;
	if (tab)
	{
		while (ft_memcmp(tab + (len * celllen), buffer, celllen))
			++len;
	}
	newtab = (void *)ft_memalloc(celllen * (len + addsize + 1));
	if (!newtab)
		return (NULL);
	if (tab)
		ft_memcpy(newtab, tab, len * celllen);
	return (newtab);
}
