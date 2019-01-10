/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:26:19 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/10 18:28:42 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static char	g_root_path[MAXPATHLEN];

__attribute__((warn_unused_result))
bool		set_root_path(void)
{
	if (getcwd(g_root_path, MAXPATHLEN) == NULL)
		return (false);
	return (true);
}

char		*simplify_path(char *path)
{
	if (!path)
		return (NULL);
	if (ft_strequ(path, "/"))
		return (g_root_path);
	return (path);
}
