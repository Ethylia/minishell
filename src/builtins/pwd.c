/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:44 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 09:19:50 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// getcwd, write
#include "util/util.h"
#include "env.h"
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
