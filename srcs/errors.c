/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 17:38:53 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/03 23:34:59 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			fatal(const char *error)
{
	//OMG 3 SYSCALLS!
	ft_perr("Fatal: ");
	ft_perr(error);
	ft_perr("\n");
	exit(-1);
}

void			errors(const char *error, const char *comment)
{
	ft_perr("Error: ");
	ft_perr(error);
	ft_perr(comment);
	ft_perr("\n");
}
