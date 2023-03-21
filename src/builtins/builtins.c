/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:03:29 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 08:56:29 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/cmd.h"
#include "../util/util.h"
#include "../def.h"
#include "builtins.h"
#include "env.h"

static const char	**get_builtins_names(void)
{
	static const char	*names[] = {BUILTIN_ECHO, BUILTIN_CD,
		BUILTIN_PWD, BUILTIN_EXPORT, BUILTIN_UNSET,
		BUILTIN_ENV, BUILTIN_EXIT, NULL};

	return (names);
}

static t_builtin_func	get_builtin_func(size_t i)
{
	static const t_builtin_func	funcs[] = {echo, cd, pwd, export,
		unset, env, bi_exit, NULL};

	return (funcs[i]);
}

int	is_builtin(t_cmd *cmd)
{
	const char	**names;
	size_t		i;

	names = get_builtins_names();
	i = 0;
	while (names[i])
	{
		if (strcmp(names[i], cmd->argv[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	get_argc(char *const argv[])
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

int	exec_builtin(t_cmd *cmd)
{
	const char				**names;
	size_t					i;

	names = get_builtins_names();
	i = 0;
	while (names[i])
	{
		if (strcmp(cmd->argv[0], names[i]) == 0)
		{
			if (get_builtin_func(i)(get_argc(cmd->argv),
				cmd->argv, *(get_exported_env())) == ERROR)
				return (ERROR);
			else
				exit(EXIT_SUCCESS);
		}
		i++;
	}
	return (ERROR);
}
