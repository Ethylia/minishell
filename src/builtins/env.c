/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:10:32 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 07:23:03 by eboyce-n         ###   ########.fr       */
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
