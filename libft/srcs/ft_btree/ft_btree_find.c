/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:38:52 by agrumbac          #+#    #+#             */
/*   Updated: 2018/06/26 18:59:55 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_btree_find uses Depth-first search
** cmp returns 0 when equal
*/

void				*ft_btree_find(t_btree *btree, const void *target, \
						int (*cmp)(const void *, const void *))
{
	t_btree			*found;

	if (!btree)
		return (NULL);
	if ((found = ft_btree_find(btree->left, target, cmp)))
		return (found);
	if ((found = ft_btree_find(btree->right, target, cmp)))
		return (found);
	if (!cmp(btree, target))
		return (btree);
	return (NULL);
}
