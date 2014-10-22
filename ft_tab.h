/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 20:03:00 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/22 21:34:07 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAB_H
# define FT_TAB_H
# define MAX_CELL_LEN 64
# include <stdlib.h>

void	*ft_tabcpy(void *tab, int addsize, size_t celllen);

void	ft_tabdel(void **tab);

void	*ft_tabncpy(void *tab, size_t len, int addsize);

int		ft_tabrealloc(void **tab, int addsize, int celllen);

#endif /* !FT_TAB_H */
