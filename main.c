/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/06 13:54:33 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/23 04:11:24 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_tab.h"


typedef struct		s_lexson
{
	char		ind;
	void		*node;
}					t_lexson;

typedef struct		s_lextree
{
	char		*content;
	char		*key;
	t_lexson	*sonlist;
}					t_slextree;

typedef t_slextree	*t_lextree;

t_lextree	*ft_getson(t_lexson *sonlist, char c)
{
	if (!sonlist)
		return (NULL);
	while (sonlist->node && sonlist->ind != c)
		++sonlist;
	return ((t_lextree *)&(sonlist->node));
}

int		ft_addson(t_lexson **sonlist_p, t_lextree node, char ind)
{
	t_lexson	*sonlist;

	if (!sonlist_p)
		return (-1);
	if (ft_tabrealloc((void **)sonlist_p, 1, sizeof(t_lexson)))
		return (-2);
	sonlist = *sonlist_p;
	while (sonlist->node)
		++sonlist;
	sonlist->node = node;
	sonlist->ind = ind;
	return (0);
}

void		ft_lextreedel(t_lextree *tree_p)
{
	if (!tree_p || !*tree_p)
		return ;
	if ((*tree_p)->content)
		ft_strdel(&((*tree_p)->content));
	if ((*tree_p)->key)
		ft_strdel(&((*tree_p)->key));
	if ((*tree_p)->sonlist)
		ft_tabdel((void **)&((*tree_p)->sonlist));
	ft_memdel((void **)tree_p);
}

t_lextree	ft_lextreenew(char *content, char *key)
{
	t_lextree	treenew;

	treenew = (t_lextree)ft_memalloc(sizeof(t_slextree));
	if (!treenew)
		return (NULL);
		// TODO: return malloc
	treenew->key = ft_strdup(key);
	treenew->content = content;
	return (treenew);
}

int			ft_lextree_insert(t_lextree *tree, void *content, char *key)
{
	int		i;
	char	*tmp;
	char	tmpc;
	t_lextree	new;
	t_lextree	*son;

	if (!tree || !*tree || !key)
		return (-1);
	i = 0;
	while (key[i] == (*tree)->key[i] && key[i])
		++i;
	if (!key[i])
	{
		if ((*tree)->key[i])
		{
			if (!(new = ft_lextreenew(content, key)))
				return (-3);
			if (ft_addson(&(new->sonlist), *tree, (*tree)->key[i]))
				return (-4);
			if (!(tmp = ft_strdup((*tree)->key + i + 1)))
				return (-5);
			ft_strdel(&((*tree)->key));
			(*tree)->key = tmp;
			*tree = new;
		}
		else
		{
			ft_memdel((void **)&((*tree)->content));
			(*tree)->content = content;
		}
	}
	else
	{
		if (!(*tree)->key[i])
		{
			if (!(son = ft_getson((*tree)->sonlist, key[i])) || !*son)
			{
				if (!(new = ft_lextreenew(content, key + i + 1)))
					return (-3);
				if (ft_addson(&((*tree)->sonlist), new, key[i]))
					return (-4);
			}
			else
				return (ft_lextree_insert(son, content, key + i + 1));
		}
		else
		{
			tmpc = key[i];
			key[i] = '\0';
			// TODO: restaurer la string sur erreur utiliser celle du tree
			if (!(new = ft_lextreenew(NULL, key)))
				return (-3);
			key[i] = tmpc;
			if (ft_addson(&(new->sonlist), *tree, (*tree)->key[i]))
				return (-4);
			if (!(tmp = ft_strdup((*tree)->key + i + 1)))
				return (-5);
			ft_strdel(&((*tree)->key));
			(*tree)->key = tmp;
			*tree = new;
			if (!(new = ft_lextreenew(content, key + i + 1)))
				return (-3);
			if (ft_addson(&((*tree)->sonlist), new, key[i]))
				return (-4);
		}
	}
	return (0);
}

int			ft_lextree_put(t_lextree tree, char *buff, int len, int (*put)(void *))
{
	t_lexson	*iter;
	int			i;

		i = -1;
		while (tree->key[++i])
			buff[len + i] = tree->key[i];
			buff[len + i] = '\0';
//	if (tree->content)
//	{
		ft_putstr(buff);
		ft_putstr(" : ");
		(*put)(tree->content);
		ft_putendl("");
//	}
	if ((iter = tree->sonlist) && iter->node)
	{
		while (iter->node)
		{
			buff[len + i] = iter->ind;
			buff[len + i + 1] = '\0';
			ft_lextree_put((t_lextree)iter->node, buff, len + i + 1, put);
			++iter;
		}
	}
	buff[len] = '\0';
	return (0);
}

int		putv(void *v)
{
	ft_putstr((char *)v);
	return (0);
}

int		main(int argc, char **argv)
{
	char	buff[256] = {'\0'};
	int		i;
	t_lextree tree = ft_lextreenew(argv[1], argv[2]);

	ft_putendl("Lextree");
	ft_putendl("tree:");
	ft_lextree_put(tree, buff, 0, putv);
	i = 3;
	while (i + 1 < argc)
	{
		ft_lextree_insert(&tree, argv[i], argv[i + 1]);
		ft_putendl("tree:");
		ft_lextree_put(tree, buff, 0, putv);
		i += 2;
	}
	ft_lextreedel(&tree);
	return (0);
}
