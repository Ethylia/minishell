/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:44 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 15:33:40 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// getcwd, write
#include <stdio.h>	// printf
#include <stdlib.h>	// free
#include "util/util.h"
#include "env.h"
#include "error.h"
#include "def.h"

int	bi_pwd(const int argc, char *const argv[], char **envp)
{
	const char	*cwd;

	(void) argc;
	(void) argv;
	(void) envp;
	cwd = get_var(envp, "PWD");
	write(STDOUT_FILENO, cwd, strln(cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
