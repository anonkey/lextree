/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 19:51:08 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/22 21:22:58 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_tabncpy(void *tab, size_t len, int addsize, size_t celllen)
{
	void	*newtab;

	if (!tab)
		return (NULL);
	newtab = (void *)ft_memalloc(celllen * (len + addsize + 1));
	if (!newtab)
		return (NULL);
		ft_memcpy(newtab, tab, celllen * len);
	return (newtab);
}
