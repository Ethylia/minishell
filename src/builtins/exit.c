/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:11:02 by francoma          #+#    #+#             */
/*   Updated: 2023/03/15 16:20:35 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"

int	bi_exit(const int argc, char *const argv[], char *const envp[])
{
	(void) argc;
	(void) argv;
	(void) envp;
	free_env(*(get_exported_env()));
	free_env(*(get_local_env()));
	exit(EXIT_SUCCESS);
	return (0);	
}
