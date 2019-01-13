/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:43:11 by agrumbac          #+#    #+#             */
/*   Updated: 2018/06/26 18:42:03 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_btree_iter uses Depth-first traversal
*/

void				ft_btree_iter(t_btree *btree, void (*f)(void *))
{
	if (!btree)
		return ;
	ft_btree_iter(btree->left, f);
	ft_btree_iter(btree->right, f);
	f(btree);
}
