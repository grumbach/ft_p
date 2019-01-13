/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_recursivedel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:38:38 by agrumbac          #+#    #+#             */
/*   Updated: 2018/06/26 15:14:43 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_btree_recursivedel(t_btree **btree, void (*del)(void *))
{
	ft_btree_iter(*btree, del);
	*btree = NULL;
}
