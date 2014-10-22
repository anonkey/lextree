/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 20:00:45 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/22 21:23:27 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_tab.h"

int		ft_tabrealloc(void **tab, int addsize, int celllen)
{
	void	**newtab;

	if (!tab)
		return (-1);
	newtab = ft_tabcpy(*tab, addsize, celllen);
	if (!newtab)
		return (-2);
	ft_tabdel(tab);
	*tab = newtab;
	return (0);
}
