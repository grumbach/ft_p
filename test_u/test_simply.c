/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_simply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 23:39:53 by gnebie            #+#    #+#             */
/*   Updated: 2018/11/19 00:01:20 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include  <stdlib.h>

char		*simplify_path(char *path);
bool		set_root_path(void);

#define TEST_SIZE 21

const char		*test_str[TEST_SIZE] = {
	"",
	"/",
	" ",
	"/../",
	"././././././.",
	"/././././././.",
	"/test_u",
	"../../../../test_u",
	"../../../srcs",
	"/",
	"/../../../srcs/../../../../test_u",
	"../test/../../bob/charles/remy/..",
	".",
	".",
	".",
	".",
	".",
	".",
	".",
	".",
	".",
};

int		main(int argc, char **argv)
{
	int		i;
	char	*path;

	i = 0;
	set_root_path();
	if (argc == 1)
	{
		while (i < TEST_SIZE)
		{
			path = simplify_path(strdup(test_str[i]));
			printf("path %i : [%s] old_path [%s]\n", i, path, test_str[i]);
			i++;
			free(path);
		}
	}
	else if (argc == 2)
	{
		char *path = simplify_path(strdup(argv[1]));
		printf("path : [%s]\n", path);
		free(path);
	}
	return (0);
}
