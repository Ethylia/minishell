/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:05:19 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 13:52:47 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>				// NULL
#include <readline/readline.h>	// rl_...
#include "readline_extra.h"
#include "error.h"
#include "def.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_sig_handlers(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit_error(SIG_INIT_ERROR_MSG);
	// if (signal(SIGQUIT, sig_handler) == SIG_ERR)
	// 	exit_error(SIG_INIT_ERROR_MSG);
}
