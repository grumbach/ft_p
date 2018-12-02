/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:11:27 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/22 17:17:24 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
**
*/

char		*get_path_from(const char *buf, const char *cmd)
{
	char		*path;

	path = ft_strstr(buf, cmd);
	if (path == NULL)
		return (NULL);

	path = path + ft_strlen(cmd);
	while (*path == ' ')//trim white spaces
		path++;

	// TODO uncomment when gnebie is done with simplify_path
	/*
	path = simplify_path(path);
	if (path == NULL)
		return(cmd_bad(sock, ERR_PERMISSION));
	*/
	return (path);
}

bool		filename_invalid(const char *filename)
{
	size_t		len;

	len = ft_strlen(filename);
	if (len == 0)
		return (true);
	while (len)
	{
		len--;
		if (!ft_isprint(filename[len]))
			return (true);
	}
	return (false);
}
