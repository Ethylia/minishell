/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:03:29 by francoma          #+#    #+#             */
/*   Updated: 2023/03/15 10:24:43 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/cmd.h"
#include "../util/util.h"
#include "builtins.h"

int	is_builtin(t_cmd *cmd)
{
	static const char *const	builtins[] = {BUILTIN_ECHO, BUILTIN_CD,
		BUILTIN_PWD, BUILTIN_EXPORT, BUILTIN_UNSET,
		BUILTIN_ENV, BUILTIN_EXIT, NULL};
	size_t						i;

	i = 0;
	while (builtins[i])
	{
		if (strcmp(builtins[i], cmd->argv[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}
