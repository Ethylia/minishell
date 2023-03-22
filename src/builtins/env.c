/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:10:32 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 14:29:28 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "env.h"

int	bi_env(const int argc, char *const argv[], char **envp)
{
	(void) argc;
	(void) argv;
	print_env(envp);
	return (SUCCESS);
}
