/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:58 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:25:38 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool			cmd_cd(int sock, char *client_input)
{
	t_ftp_header	answer;
	size_t			body_size;

	body_size = ft_strlen(client_input) + 1;
	if (send_answer(sock, CMD_CD, body_size, client_input) == false)
		return (false);
	if (receive_answer(sock, &answer) == false)
		return (false);
	return (true);
}
