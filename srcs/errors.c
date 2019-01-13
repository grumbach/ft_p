/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 17:38:53 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/12 16:39:05 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			fatal(const char *error)
{
	ft_perr(FTP_FATAL);
	ft_perr(error);
	ft_perr("\n");
	exit(EXIT_FAILURE);
}

void			warn(const char *warning)
{
	ft_printf("%s%s\n", FTP_WARN, warning);
}
