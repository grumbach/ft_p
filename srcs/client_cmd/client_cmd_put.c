/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:55 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:26:51 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool			cmd_put(int sock, char *client_input)
{
	char		*filename;
	char		*file;
	size_t		filename_size;
	size_t		file_size;

	filename = get_filename_from(client_input);
	if (filename == NULL)
	{
		warn("filename invalid");
		return (true);
	}
	file = read_file(client_input, &file_size);
	if (file == NULL)
	{
		warn("failed to read file");
		return (true);
	}
	filename_size = ft_strlen(filename) + 1;
	if (send_request(sock, CMD_PUT, filename_size, filename) == false)
		return (false);
	if (send_request(sock, CMD_PUT, file_size, file) == false)
		return (false);
	free_file(file, file_size);
	return (true);
}
