/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:06 by agrumbac          #+#    #+#             */
/*   Updated: 2018/10/31 20:25:45 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
**
*/

__NO_RETURN
void			signal_handler(int sig)
{
	//TODO manage errors
	server_cleanup();
	exit(0);
}

__NO_RETURN
static void		fatal(const char *error)
{
	exit(-1);
}

__NO_RETURN
static void		child_code()
{
	//TODO ft_p happens here
}

__NO_RETURN
static void		accept_loop()
{
	while (1)
	{
		accept(); //mostly blocks here

		if (fd == -1)
			fatal("accept failed");
		else
		{
			pid = fork();
			if (pid == 0) //if child
				child_code();

			//father stays in the loop
		}
	}
}

__NO_RETURN
void			main(int ac, char **av)
{
	parse_args();

	server_init();

	signal(0 /* what is sig? */, &signal_handler);

	accept_loop();
}
