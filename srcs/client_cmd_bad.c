/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_bad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:46:40 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 20:18:19 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool			cmd_bad(__unused int sock, char *client_input)
{
	if (client_input[0] != '\n')
		ft_printf("\e[33m[WARNING] \e[0munrecognized command\n");
	return (true);
}
