/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:58 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/12 16:37:06 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

__attribute__((warn_unused_result))
bool			cmd_cd(int sock, char *client_input)
{
	t_ftp_header	answer;
	size_t			body_size;

	body_size = ft_strlen(client_input) + 1;

	send_request(sock, CMD_CD, body_size);

	send(sock, client_input, body_size, 0);

	if (receive_answer(sock, &answer) == false)
		return (false);

	return (true);
}
