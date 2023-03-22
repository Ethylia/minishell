/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:33:44 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 14:25:51 by eboyce-n         ###   ########.fr       */
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
	{
		print_err("pwd");
		return (ERROR);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}
