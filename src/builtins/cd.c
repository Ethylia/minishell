/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:30:41 by francoma          #+#    #+#             */
/*   Updated: 2023/03/23 10:10:04 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// free
#include <unistd.h>	// write
#include "../util/util.h"
#include "../def.h"
#include "../env.h"
#include "data.h"
#include "cd.h"

#define MSG_OLDPWD_NOT_SET "minishell: cd: OLDPWD not set\n"
#define MSG_HOME_NOT_SET "minishell: cd: HOME not set\n"

static const char	*get_home(char **envp)
{
	const char	*path;

	path = get_var(envp, "HOME");
	if (!path)
	{
		write(STDERR_FILENO, MSG_HOME_NOT_SET, strln(MSG_HOME_NOT_SET));
		return (NULL);
	}
	return (path);
}

static const char	*get_oldpwd(char **envp)
{
	const char	*path;

	path = get_var(envp, "OLDPWD");
	if (!path)
	{
		write(STDERR_FILENO, MSG_OLDPWD_NOT_SET, strln(MSG_OLDPWD_NOT_SET));
		return (NULL);
	}
	print_path(envp, path);
	return (path);
}

static char	*resolve_home(char **envp, char *argv)
{
	char		*path;
	const char	*home;

	home = get_home(envp);
	if (!home)
		return (NULL);
	path = concatstr(2, home, argv + 1);
	return (path);
}

// if stdin: don't cd
// no arg: cd $(HOME)
// arg1: path
// arg2+: ignored

// ~							: cd $HOME
// -							: cd $OLDPWD, pwd
// /							: separator
// .							: (pwd)
// ..							: (remove last dir of pwd)
// does not start with /		: modifies pwd
// set $PWD $OLDPWD
int	bi_cd(const int argc, char *const argv[], char **envp)
{
	const char	*path;
	char		*resolved_path;

	resolved_path = NULL;
	if (argc == 1)
		path = get_home(envp);
	else if (strcmp(argv[1], "-") == 0)
		path = get_oldpwd(envp);
	else if (starts_with(argv[1], "~"))
	{
		resolved_path = resolve_home(envp, argv[1]);
		path = resolved_path;
	}
	else
		path = argv[1];
	if (!path || chdir(path) == ERROR)
	{
		if (path)
			perror(path);
		return (ERROR);
	}
	free(resolved_path);
	update_oldpwd((char **)envp);
	update_pwd((char **)envp);
	return (SUCCESS);
}
