/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/06 13:54:33 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/19 20:51:34 by tseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>


typedef struct		s_lexson
{
	char		ind;
	void		*node;
}					t_lexson;

typedef struct		s_lextree
{
	char		*content;
	char		*key;
	t_lexson	*listson;
}					t_slextree;

typedef t_slextree	*t_lextree;

void	ft_lextreedel(t_lextree *tree_p)
{
	if (!tree_p || !*tree_p)
		return ;
	if ((*tree_p)->content)
		ft_strdel(&((*tree_p)->content));
	if ((*tree_p)->key)
		ft_strdel(&((*tree_p)->key));
	if ((*tree_p)->listson)
		ft_tabdel(&((*tree_p)->listson));
	ft_memdel((void **)tree_p);
}

t_lextree	ft_lextreenew(char *content, char *key)
{
	t_lextree	treenew;

	treenew = (t_lextree)ft_memalloc(sizeof(t_slextree));
	if (!treenew)
		return (NULL);
	treenew->key = key;
	treenew->content = content;
	return (treenew);
}

static int	ft_lextree_soninsert(t_ldcd listson, char *word, char *key)
{
	t_ldcd_cell		iter;
	t_lextree		newson;

	iter = listson->head;
	while (iter
			&& -2 == (ft_lextree_insert((t_lextree)iter->content, word, key)))
	{
		iter = iter->next;
	}
	if (!iter)
	{
		newson = ft_lextreenew();
		if (!newson)
			return (-1);
		if (0 > ft_lextree_insert(newson, word, key))
			return (-2);
		return (ft_ldcdpush_back(listson, newson, sizeof(t_slextree)));
	}
	return (0);
}

int			ft_lextree_insert(t_lextree tree, char *word, char *key)
{
	char	*firstson;
	char	*newson;
	char	*act;

	if (!tree || !word || !key)
		return (-1);
	if (!tree->content)
	{
		tree->content = ft_strdup(word);
		tree->key = ft_strdup(key);
		return (0);
	}
	ind = ft_strindcmp(tree->content, word);
	if (ind == 0)
		return (-2);
	act = ft_strsub(tree->content, 0, ind + 1);
	firstson = ft_strsub(tree->content, ind, ft_strlen(tree->content) - ind);
	newson = ft_strsub(word, ind, ft_strlen(word) - ind);
	if (0 > ft_lextree_soninsert(tree->listson, firstson))
		return (-3);
	if (ft_lextree_soninsert(tree->listson, newson))
		return (-4);
	return (0);
}

int		main(void)
{
	t_lextree tree = ft_lextreenew();

	ft_lextreedel(&tree);
	return (0);
}
