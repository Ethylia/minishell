/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:03:29 by francoma          #+#    #+#             */
/*   Updated: 2023/03/24 11:20:24 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/cmd.h"
#include "util/util.h"
#include "def.h"
#include "builtins.h"
#include "env.h"
#include "data.h"
#include "redir.h"

const char	**get_builtins_names(void)
{
	static const char	*names[] = {BUILTIN_ECHO, BUILTIN_CD,
		BUILTIN_PWD, BUILTIN_EXPORT, BUILTIN_UNSET,
		BUILTIN_ENV, BUILTIN_EXIT, NULL};

	return (names);
}

t_builtin_func	get_builtin_func(size_t i)
{
	static const t_builtin_func	funcs[] = {bi_echo, bi_cd, bi_pwd, bi_export,
		bi_unset, bi_env, bi_exit, NULL};

	return (funcs[i]);
}

int	is_builtin(t_cmd *cmd)
{
	const char	**names;
	size_t		i;

	if (!cmd->argv[0])
		return (0);
	names = get_builtins_names();
	i = 0;
	if (isalphaunder(cmd->argv[0][0]) && strchar(cmd->argv[0], '=')
		&& stralphanumunder(cmd->argv[0]))
		return (1);
	while (names[i])
	{
		if (strcmp(names[i], cmd->argv[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}
