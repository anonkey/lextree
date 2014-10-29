/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseguier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/06 13:54:33 by tseguier          #+#    #+#             */
/*   Updated: 2014/10/29 03:55:00 by garm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_tab.h"


typedef struct		s_lexson
{
	char		ind;
	void		*node;
}					t_lexson;

typedef struct		s_lextree
{
	void		*content;
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

void		ft_lextreedel(t_lextree *tree_p, void (*del)(void **))
{
	int		i;

	i = 0;
	if (!tree_p || !*tree_p)
		return ;
	if ((*tree_p)->content && del)
		(*del)(&((*tree_p)->content));
	if ((*tree_p)->key)
		ft_strdel(&((*tree_p)->key));
	if ((*tree_p)->sonlist)
	{
		while ((*tree_p)->sonlist[i].node)
			ft_lextreedel((t_lextree *)&(((*tree_p)->sonlist)[i++].node), del);
		ft_tabdel((void **)&((*tree_p)->sonlist));
	}
	ft_memdel((void **)tree_p);
}

t_lextree	ft_lextreenew(void *content, char *key)
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

int			ft_lextree_insert(t_lextree *tree, void *content, char *key, void (*del)(void **))
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
			(*del)(&((*tree)->content));
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
				return (ft_lextree_insert(son, content, key + i + 1, del));
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
	if (tree->content)
	{
		(*put)(tree->content);
		ft_putstr(" ");
		ft_putstr(buff);
		ft_putendl("");
	}
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
	buff[len + i] = '\0';
	return (0);
}

int	ft_lextree_comp(t_lextree tree, char *start, char *key, int (*put)(void *))
{
	t_lextree	*son_p;
	int		i;

	i = 0;
	while (tree->key[i] && tree->key[i] == key[i])
		++i;
	if (!key[i])
	{
		return (ft_lextree_put(tree, start, ft_strlen(start) - i, put));
	}
	if (!tree->key[i])
	{
		if (!(son_p = ft_getson(tree->sonlist, key[i])) || !*son_p)
			 return (-1);
		return (ft_lextree_comp(*son_p, start, key + i + 1, put));
	}
	else
		return (-1);
}

void		*ft_lextree_get(t_lextree tree, char *key)
{
	t_lextree	*son_p;
	int			i;

	i = 0;
	while (tree->key[i] && tree->key[i] == key[i])
		++i;
	if (!key[i])
	{
		if (tree->key[i])
			return (NULL);
		return (tree->content);
	}
	if (!tree->key[i])
	{
		if (!(son_p = ft_getson(tree->sonlist, key[i])) || !*son_p)
			return (NULL);
		return (ft_lextree_get(*son_p, key + i + 1));
	}
	else
		return (NULL);
}

int		putv(void *v)
{
	ft_putstr((char *)v);
	return (0);
}

int		main(int argc, char **argv)
{
	char	buff[256] = {'\0'};
	char	**tab;
	char	*line;
	t_lextree tree = ft_lextreenew(ft_strdup(argv[1]), argv[2]);
	int		i;
	size_t	size;

	//ft_putendl("Lextree");
	//ft_putendl("tree:");
	//ft_lextree_put(tree, buff, 0, putv);
	if (argc < 4)
		return (-1);
	size = 0;
	while (0 < get_next_delim(0, &line, '\n'))
	{
	i = 0;
		ft_bzero(buff, 256);
	//	ft_putendl(line);
		if (!(tab = ft_strsplit(line, '=')))
			return (-1);
		//ft_putstr("value : ");ft_putstr(tab[0]); ft_putstr("| key : ");ft_putendl(tab[1]);
		if (*tab && tab[1])
		{
			size += ft_strlen(tab[i]) + ft_strlen(tab[i + 1]);
			ft_lextree_insert(&tree, ft_strdup(tab[i]), tab[i + 1], &ft_memdel);
				i += 2;
		}
		ft_strtabdel(&tab);
		free(line);
	//	ft_strtabdel(&tab);
	//	ft_putendl("tree:");
	//	ft_lextree_put(tree, buff, 0, putv);
	}
		//free(line);
//	ft_putnbr_ull(size);
//		ft_putendl("---------");
	ft_lextree_put(tree, buff, 0, putv);
//		ft_putendl("---------");
	//	pause();
		ft_putendl(ft_lextree_get(tree, argv[3]));
		ft_putnbr(ft_lextree_comp(tree, argv[3], argv[3], &putv));
	ft_lextreedel(&tree, &ft_memdel);
	return (0);
}
