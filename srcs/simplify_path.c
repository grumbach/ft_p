
#include "ft_p.h"
#include <sys/param.h>
#include <unistd.h>

static char g_root_path[MAXPATHLEN];

typedef struct		s_array
{
	char	**ptr;
	size_t	size;
	size_t	real_size;
}					t_array;

/*
** Ne pas rm -rf ce qu'il y a au dessus ! de ce commentaire
*/

char *ft_strjoin(char *s1, char *s2)
{
	char *s3;

	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strcpy(s3, s1);
	ft_strcpy(s3 + ft_strlen(s1), s2);
	return (s3);
}

size_t		ft_strnlen(const char *str, size_t len)
{
	size_t		size;

	size = 0;
	while (size < len && str[size])
		size++;
	return (size);
}

char		*ft_strndup(const char *str, size_t len)
{
	size_t		size;
	char		*newstr;

	size = ft_strnlen(str, len);
	if ((newstr = ft_memalloc(size + 1)) == NULL)
		return (NULL);
	ft_memcpy(newstr, str, size);
	return (newstr);
}

char		*get_real_path(char *path)
{
	char				*new_path;
	char				pwd_path[MAXPATHLEN];
	char				*pwd_server;
	int					root_path_size;
	const char *		const_global_real_path;

	const_global_real_path = g_root_path;
	if (path[0] == '/')
		new_path = ft_strdup(path);
	else
	{
		root_path_size = ft_strlen(const_global_real_path);
		if (getcwd(pwd_path, MAXPATHLEN) == NULL
			|| ft_strncmp(const_global_real_path, pwd_path, root_path_size))
			return (ft_strdup("/"));
		pwd_server = &pwd_path[root_path_size];
		if (pwd_server[0])
			new_path = ft_strjoin(pwd_server, path);
		else
			new_path =  ft_strdup(path);
	}
	return (new_path);
}

void		*array_remove_elem(t_array *array, size_t elem_index)
{
	void		*elem;

	if (elem_index >= array->size)
		return (NULL);
	elem = array->ptr[elem_index];
	while (elem_index + 1 < array->size)
	{
		array->ptr[elem_index] = array->ptr[elem_index + 1];
		elem_index++;
	}
	array->size--;
	array->ptr[elem_index] = NULL;
	return (elem);
}

void		array_delete_elem(t_array *array, size_t elem_index, void (*d)(void *))
{
	void		*elem;

	elem = array_remove_elem(array, elem_index);
	d(elem);
}

void		array_delete_prev(t_array *array, size_t elem_index, void (*d)(void *))
{
	void		*elem;

	if (elem_index > 0)
	{
		elem = array_remove_elem(array, elem_index - 1);
		d(elem);
	}
}

t_array			*remove_path_returns(t_array *path_tab)
{
	size_t			i;

	i = 0;
	while (i < path_tab->size)
	{
		if (!ft_strcmp(path_tab->ptr[i], ".."))
		{
			array_delete_elem(path_tab, i, free);
			if (i > 0)
			{
				i--;
				array_delete_elem(path_tab, i, free);
			}
		}
		else if (!ft_strcmp(path_tab->ptr[i], "."))
			array_delete_elem(path_tab, i, free);
		else
			i++;
	}
	return (path_tab);
}

static size_t		count_array_elems(const char *str, char spliter)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while(str[i])
	{
		while(str[i] && str[i] == spliter)
			i++;
		if (str[i])
			count++;
		while(str[i] && str[i] != spliter)
			i++;
	}
	return (count);
}

static void		add_elems(const char *str, char spliter, char **str_tab)
{
	size_t		i;
	size_t		count;

	i = 0;
	while(str[i])
	{
		while(str[i] && str[i] == spliter)
			i++;
		count = i;
		while(str[i] && str[i] != spliter)
			i++;
		if (i > count)
		{
			*str_tab = ft_strndup(&str[count], i - count);
			str_tab++;
		}
	}
}

void		*ft_strsplit_to_array(const char *str, char spliter)
{
	size_t		count;
	t_array		*array;

	if (str == NULL)
		return (NULL);
	count = count_array_elems(str, spliter);
	if ((array = ft_memalloc(sizeof(t_array))) == NULL)
		return (NULL);
	if ((array->ptr = ft_memalloc(count * sizeof(char *))) == NULL)
	{
		free(array);
		return (NULL);
	}
	array->size = count;
	array->real_size = count;
	add_elems(str, spliter, array->ptr);
	return (array);
}

void		ft_array_del(t_array *array)
{
	size_t		i;

	i = 0;
	while (i < array->size)
	{
		free(array->ptr[i]);
		i++;
	}
	free(array->ptr);
	free(array);
}

static size_t	ft_concat_array_find_len(t_array *array, char *concat_str)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (i < array->size)
	{
		len += ft_strlen(concat_str);
		if (array->ptr[i])
			len += ft_strlen(array->ptr[i]);
		i++;
	}
	return (len);
}

static char		*ft_concat_array_fill_str(t_array *array,
	char *concat_str, size_t max_len, char *str)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (i < array->size)
	{
		if (array->ptr[i])
		{
			ft_strncat(&str[len], concat_str, max_len - len);
			len += ft_strlen(concat_str);
			ft_strncat(&str[len], array->ptr[i], max_len - len);
			len += ft_strlen(array->ptr[i]);
		}
		i++;
	}
	return (str);
}

static char		*ft_concat_array(t_array *array, char *concat_str)
{
	size_t		len;
	char		*str;

	len = ft_concat_array_find_len(array, concat_str);
	if ((str = ft_memalloc(len + 1)) == NULL)
		return (NULL);
	ft_concat_array_fill_str(array, concat_str, len, str);
	return (str);
}

char		*ft_concat_and_delete_array(t_array *array, char *concat_str)
{
	char		*str;

	str = ft_concat_array(array, concat_str);
	ft_array_del(array);
	return (str);
}

char		*add_root(char *path)
{
	char		*new_path;

	new_path = ft_strjoin(g_root_path, path);
	free(path);
	return (new_path);
}

/*
** *********************** Tout le code avant cette ligne ne sert a rien et doit etre rm -rf
** *********************** Je le garde juste pour que mon fichier fasse 300 ligne et soit plein de mallocs
** *********************** Et q'il dise que c'est horrible jusqu'a tomber sur ce commentaire
** *********************** et etre super content de pouvoir rm -rf tout ce qu'il y a au dessus
*/

bool		set_root_path(void)
{
	if (getcwd(g_root_path, MAXPATHLEN) == NULL)
		return (false);
	return (true);
}


static void		clean_tmp_path(char *path_tmp)
{
	int			i;
	int			j;

	i = 0;
	while (path_tmp[i])
	{
		if (!ft_strncmp(&path_tmp[i], "//", 2))
			ft_strcpy(&path_tmp[i], &path_tmp[i + 1]);
		else if (!ft_strncmp(&path_tmp[i], "/../", 4))
		{
			ft_strcpy(&path_tmp[i], &path_tmp[i + 3]);
			if (i != 0)
			{
				j = i - 1;
				while (j > 0 && path_tmp[j] != '/')
					j--;
				ft_strcpy(&path_tmp[j + 1], &path_tmp[i]);
				i = j;
			}
		}
		else if (!ft_strncmp(&path_tmp[i], "/./", 3))
			ft_strcpy(&path_tmp[i], &path_tmp[i + 2]);
		else
			i++;
	}
	ft_printf("path clean find : %s \n", path_tmp); // TODO delete debbug infos
}

char		*simplify_path(char *path)
{
	char		path_tmp[MAXPATHLEN * 2];
	size_t		len_gpath;

	len_gpath = ft_strlen(g_root_path);

	ft_printf("path origin : %s %li\n", g_root_path, len_gpath); // TODO delete debbug infos
	ft_printf("path give : %s %li\n", path, len_gpath);// TODO delete debbug infos

	if (!path) // assume que path fait toujours moins que MAXPATHLEN
		return (NULL);

	if (path[0] == '/')
		ft_strncpy(path_tmp, path, MAXPATHLEN);
	else
	{
		getcwd(path_tmp, MAXPATHLEN);
		if (ft_strncmp(path_tmp, g_root_path, len_gpath))
			return (NULL);
		ft_strcpy(path_tmp, &path_tmp[len_gpath]); // Buffer overflow ??
		// path_tmp[ft_strlen(path_tmp) - len_gpath] = 0;
		ft_strncat(path_tmp, "/", 2);
		ft_strncat(path_tmp, path, ft_strlen(path));
	}

	ft_printf("path find : %s \n", path_tmp);// TODO delete debbug infos
	if (path_tmp[0] != '/') // overprotection for the tests // TODO delete it
	{
		warn("path invalid");
		ft_printf("path invalid : %s \n", path_tmp);// TODO delete debbug infos
		return (NULL);
	}

	clean_tmp_path(path_tmp);
	if (ft_strlen(path_tmp) + ft_strlen(g_root_path) > MAXPATHLEN)
		return (NULL);
	ft_strcpy(path, g_root_path);
	ft_strncat(path, path_tmp, ft_strlen(path_tmp));

	ft_printf("path final find : %s \n", path);// TODO delete debbug infos
	// return le buffer envoyé
	return (ft_strdup(path)); // TODO enlever le strdup quand free enlevés
}
