/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:44 by francoma          #+#    #+#             */
/*   Updated: 2023/03/24 11:02:33 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// getcwd, write
#include <stdio.h>	// printf
#include <stdlib.h>	// free
#include "../util/util.h"
#include "../error.h"
#include "../def.h"

int	bi_pwd(const int argc, char *const argv[], char **envp)
{
	char	*cwd;

	(void) argc;
	(void) argv;
	(void) envp;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (print_err("pwd"));
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}
