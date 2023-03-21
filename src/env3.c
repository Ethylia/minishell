/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:57:21 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 15:51:39 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"

char	***get_exported_env(void)
{
	static char	**env;

	return (&env);
}

void	set_exported_env(char	*env[])
{
	*(get_exported_env()) = copy_env(env);
}

char	***get_local_env(void)
{
	static char	**env;

	return (&env);
}
