/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:11:02 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 08:21:13 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include "readline_extra.h"
#include "env.h"
#include "data.h"

int	bi_exit(const int argc, char *const argv[], char *const envp[])
{
	(void) argc;
	(void) argv;
	(void) envp;
	rl_clear_history();
	// free les autres trucs
	// free_env(*(get_exported_env()));
	// free_env(*(get_local_env()));
	freedata();
	exit(EXIT_SUCCESS);
	return (0);
}
