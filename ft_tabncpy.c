/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 19:51:08 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/19 19:59:06 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	**ft_tabncpy(void **tab, size_t len, int addsize)
{
	void	**newtab;

	if (!tab)
		return (NULL);
	newtab = (void **)malloc(sizeof(void *) * (len + addsize + 1));
	if (!newtab)
		return (NULL);
	newtab[len] = NULL;
	while (len-- > 0)
		newtab[len] = tab[len];
	return (newtab);
}
