/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/24 18:59:15 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/24 19:36:46 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

int		main(void)
{
	//char	**tab;
	char	*line;

	while (0 < get_next_delim(0, &line, '\n'))
	{
		//tab = ft_strsplit(line, '=');
		free(line);
	//	ft_strtabdel(&tab);
	}
return (0);
}