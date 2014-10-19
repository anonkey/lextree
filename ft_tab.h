/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/19 20:03:00 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/19 20:09:13 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAB_H
# define FT_TAB_H

void		**ft_tabcpy(void **tab, int addsize);

void		ft_tabdel(void ***tab);

void		**ft_tabncpy(void **tab, size_t len, int addsize);

int			ft_tabrealloc(void ***tab, int addsize);

#endif /* !FT_TAB_H */