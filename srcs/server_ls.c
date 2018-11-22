/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 03:45:20 by gnebie            #+#    #+#             */
/*   Updated: 2018/11/19 03:45:21 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"



int		server_error()
{
	;
}

bool		send_ls()
{
	while ((buff_size = read(buf)) != -1)
	{
		send(buff_size);
		send(buf);
		if (buff_size != BUFF_SIZE)
			return (true);
	}
	return (false);
}



int		server_ls()
{
	char		**argv_cmd;
	pid_t			pid_son;

	if ((argv_cmd = get_argv_cmd()) == NULL)
		return (server_error());


	if (pid_son == -1)
		return (server_error()); // cmd_bad
	if (wait_son());
		return (false);
	int		ret;
	ret = send_ls();
	return (ret);
}
