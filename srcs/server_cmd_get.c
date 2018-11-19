/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:12 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:54:20 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_get(int sock, uint64_t body_size)
{
	ft_printf("cmd_get");
}
//{open() fstat() mmap() send(file.size), send(file) munmap()}
