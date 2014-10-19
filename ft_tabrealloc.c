/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 20:00:45 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/19 20:09:29 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_tab.h"

int		ft_tabrealloc(void ***tab, int addsize)
{
	void	**newtab;

	if (!tab || !*tab)
		return (-1);
	newtab = ft_tabcpy(*tab, addsize);
	if (!newtab)
		return (-2);
	ft_tabdel(tab);
	*tab = newtab;
	return (0);
}
