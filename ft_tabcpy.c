/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 19:49:10 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/19 19:57:13 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	**ft_tabcpy(void **tab, int addsize)
{
	size_t		len;
	void	**newtab;

	len = 0;
	if (!tab)
		return (NULL);
	while (tab[len])
		len++;
	newtab = (void **)malloc(sizeof(void *) * (len + addsize + 1));
	if (!newtab)
		return (NULL);
	while (len-- > 0)
		newtab[len] = tab[len];
	return (newtab);
}
