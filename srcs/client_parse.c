/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:20:44 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:21:21 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static const char	*cmd_str[] =
{
	[CMD_BAD] = "invalid command",
	[CMD_LS] = "ls ",//how about plain ls?
	[CMD_MKDIR] = "mkdir ",
	[CMD_CD] = "cd ",
	[CMD_GET] = "get ",
	[CMD_PUT] = "put ",
	[CMD_PWD] = "pwd",
	[CMD_QUIT] = "quit"
};

enum e_cmd			determine_command(const char *command)
{
	return (CMD_BAD
	|	CMD_LS * !ft_strncmp(cmd_str[CMD_LS], command, 3)
	|	CMD_MKDIR * !ft_strncmp(cmd_str[CMD_MKDIR], command, 6)
	|	CMD_CD * !ft_strncmp(cmd_str[CMD_CD], command, 3)
	|	CMD_GET * !ft_strncmp(cmd_str[CMD_GET], command, 4)
	|	CMD_PUT * !ft_strncmp(cmd_str[CMD_PUT], command, 4)
	|	CMD_PWD * !ft_strncmp(cmd_str[CMD_PWD], command, 4)
	|	CMD_QUIT * !ft_strncmp(cmd_str[CMD_QUIT], command, 5));
}
