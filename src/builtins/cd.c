/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:30:41 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 15:56:42 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// free
#include <stdio.h>	// printf
#include <unistd.h>	// getcwd
#include "../util/util.h"
#include "../env.h"
#include "../def.h"

static void	print_path(char *const envp[], const char *path)
{
	const char	*home;

	home = get_var(envp, "HOME");
	if (starts_with(home, path))
		printf("~%s\n", path + strln(home));
	else
		printf("%s\n", path);
}

static int	update_oldpwd(char **envp)
{
	char	*oldpwd;

	oldpwd = concatstr(2, "OLDPWD=", get_var(envp, "PWD"));
	if (!oldpwd)
		return (ERROR);
	envp = update_env(envp, oldpwd);
	free(oldpwd);
	if (!envp)
		return (ERROR);
	return (SUCCESS);
}

static int	update_pwd(char **envp)
{
	char	*path;
	char	*pwd;

	path = getcwd(NULL, 0);
	pwd = concatstr(2, "PWD=", path);
	free(path);
	if (!pwd)
		return (ERROR);
	envp = update_env((char **)envp, pwd);
	free(pwd);
	if (!envp)
		return (ERROR);
	return (SUCCESS);
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
int	cd(const int argc, char *const argv[], char *const envp[])
{
	char	*path;

	if (argc == 0)
		path = getenv("HOME");
	else if (strcmp(argv[1], "-") == 0)
	{
		path = getenv("OLDPWD");
		print_path(envp, path);
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		perror(path);
		return (ERROR);
	}
	update_oldpwd((char **)envp);
	update_pwd((char **)envp);
	return (SUCCESS);
}
