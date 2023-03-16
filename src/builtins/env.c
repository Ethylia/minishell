/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:10:32 by francoma          #+#    #+#             */
/*   Updated: 2023/03/15 16:02:34 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "env.h"

int	env(const int argc, char *const argv[], char *const envp[])
{
	(void) argc;
	(void) argv;
	print_env(envp);
	return (SUCCESS);	
}
