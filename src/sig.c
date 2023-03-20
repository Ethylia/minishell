/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:05:19 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 14:36:43 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>				// NULL
#include <readline/readline.h>	// rl_...
#include "readline_extra.h"
#include "error.h"
#include "def.h"

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		// if exit code is 131,
		//	printf("Quit: %d\n", signo);

	}
}

void	init_sig_handlers(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_error(SIG_INIT_ERROR_MSG);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		exit_error(SIG_INIT_ERROR_MSG);
}
