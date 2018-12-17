/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:20:44 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/17 05:49:15 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

# define LEXER_LS			"ls"
# define LEXER_MKDIR		"mkdir"
# define LEXER_CD			"cd"
# define LEXER_GET			"get"
# define LEXER_PUT			"put"
# define LEXER_PWD			"pwd"
# define LEXER_QUIT			"quit"

static const char	*cmd_str[] =
{
	[CMD_LS] = LEXER_LS,
	[CMD_MKDIR] = LEXER_MKDIR,
	[CMD_CD] = LEXER_CD,
	[CMD_GET] = LEXER_GET,
	[CMD_PUT] = LEXER_PUT,
	[CMD_PWD] = LEXER_PWD,
	[CMD_QUIT] = LEXER_QUIT
};

static const size_t	cmd_len[] =
{
	[CMD_LS] = sizeof(LEXER_LS) - 1,
	[CMD_MKDIR] = sizeof(LEXER_MKDIR) - 1,
	[CMD_CD] = sizeof(LEXER_CD) - 1,
	[CMD_GET] = sizeof(LEXER_GET) - 1,
	[CMD_PUT] = sizeof(LEXER_PUT) - 1,
	[CMD_PWD] = sizeof(LEXER_PWD) - 1,
	[CMD_QUIT] = sizeof(LEXER_QUIT) - 1
};

/*
** lexer
** - writes a pointer to the argument in client_input into input_arg
** - returns found command code
** - returns -1 if input is empty
*/

int					lexer(const char *client_input, char **input_arg)
{
	enum e_cmd		cmd;

	while (ft_isspace(*client_input))
		client_input++;

	// check for empty input
	if (*client_input == '\0')
		return (-1);

	// identify command
	cmd = CMD_BAD
	| CMD_LS * !ft_strncmp(cmd_str[CMD_LS], client_input, cmd_len[CMD_LS])
	| CMD_MKDIR * !ft_strncmp(cmd_str[CMD_MKDIR], client_input, cmd_len[CMD_MKDIR])
	| CMD_CD * !ft_strncmp(cmd_str[CMD_CD], client_input, cmd_len[CMD_CD])
	| CMD_GET * !ft_strncmp(cmd_str[CMD_GET], client_input, cmd_len[CMD_GET])
	| CMD_PUT * !ft_strncmp(cmd_str[CMD_PUT], client_input, cmd_len[CMD_PUT])
	| CMD_PWD * !ft_strncmp(cmd_str[CMD_PWD], client_input, cmd_len[CMD_PWD])
	| CMD_QUIT * !ft_strncmp(cmd_str[CMD_QUIT], client_input, cmd_len[CMD_QUIT]);

	// check for separator
	client_input += cmd_len[cmd];
	ft_printf("[%d] %d '%c'\n", cmd , *client_input, *client_input);
	if (*client_input != '\0' && !ft_isspace(*client_input))
		return (CMD_BAD);

	// identify arg
	while (ft_isspace(*client_input))
		client_input++;
	*input_arg = (char *)client_input;

	return (cmd);
}
