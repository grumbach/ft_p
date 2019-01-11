/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:26:19 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/11 21:27:19 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static char			g_root_path[MAXPATHLEN];
static size_t		g_root_path_len;

/*
** set_root_path:
**   initializer for g_root_path and g_root_path_len
**   must be called at startup
*/

__attribute__((warn_unused_result))
bool			set_root_path(void)
{
	if (getcwd(g_root_path, MAXPATHLEN) == NULL)
		return (false);
	g_root_path_len = ft_strlen(g_root_path);
	return (true);
}

/*
** root_path_len:
**   getter for g_root_path_len
*/

size_t			root_path_len(void)
{
	return (g_root_path_len);
}

/*
** simplify_path:
**   simplifies path given, returns path
**   path must be MAXPATHLEN
*/

static void		clean_tmp_path(char *path)
{
	int			i;
	int			j;

	i = 0;
	while (path[i])
	{
		if (!ft_strncmp(&path[i], "/../", 4) || !ft_strcmp(&path[i], "/.."))
		{
			ft_strcpy(&path[i], &path[i + 3]);
			if (i != 0)
			{
				j = i - 1;
				while (j > 0 && path[j] != '/')
					j--;
				ft_strcpy(&path[j + 1], &path[i]);
				i = j;
			}
		}
		else if (!ft_strncmp(&path[i], "//", 2))
			ft_strcpy(&path[i], &path[i + 1]);
		else if (!ft_strncmp(&path[i], "/./", 3) || !ft_strcmp(&path[i], "/."))
			ft_strcpy(&path[i], &path[i + 2]);
		else
			i++;
	}
}

__attribute__((nonnull))
char			*simplify_path(char *path)
{
	char		path_tmp[MAXPATHLEN * 2];

	path[MAXPATHLEN - 1] = '\0'; // TODO remove tmp security after issue #12 fix
	if (path[0] == '/')
		ft_strncpy(path_tmp, path, MAXPATHLEN);
	else
	{
		getcwd(path_tmp, MAXPATHLEN);
		if (ft_strncmp(path_tmp, g_root_path, g_root_path_len))
			return (NULL);
		ft_strcpy(path_tmp, &path_tmp[g_root_path_len]);
		ft_strncat(path_tmp, "/", 2);
		ft_strcat(path_tmp, path);
	}

	clean_tmp_path(path_tmp);
	if (ft_strlen(path_tmp) + g_root_path_len >= MAXPATHLEN)
		return (NULL);
	ft_strcpy(path, g_root_path);
	ft_strcat(path, path_tmp);
	return (path);
}
