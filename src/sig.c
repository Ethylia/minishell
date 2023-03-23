/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:05:19 by francoma          #+#    #+#             */
/*   Updated: 2023/03/23 16:13:03 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>				// NULL
#include <readline/readline.h>	// rl_...
#include "readline_extra.h"
#include "error.h"
#include "def.h"
#include "data.h"
#include "env.h"
#include <unistd.h>

static void	sig_handler(int signo)
{
	if (signo == SIGINT && isatty(STDOUT_FILENO))
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		if (getdata()->intflag)
			rl_redisplay();
	}
	else if (signo == SIGQUIT && isatty(STDOUT_FILENO))
		rl_redisplay();
}

void	init_sig_handlers(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_error(SIG_INIT_ERROR_MSG);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		exit_error(SIG_INIT_ERROR_MSG);
}
