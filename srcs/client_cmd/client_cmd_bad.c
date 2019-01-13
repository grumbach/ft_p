/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_bad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:46:40 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:15:48 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool			cmd_bad(int sock, char *client_input)
{
	(void)sock;
	(void)client_input;
	warn("unrecognized command");
	return (true);
}
