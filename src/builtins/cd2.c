/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:31:49 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 14:10:00 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../util/util.h"
#include "../def.h"
#include "../env.h"
#include "data.h"

void	print_path(char *const envp[], const char *path)
{
	const char	*home;

	home = get_var(envp, "HOME");
	if (starts_with(path, home))
		printf("~/%s\n", path + strln(home));
	else
		printf("%s\n", path);
}

void	updateps1(const char *path)
{
	char				*ps1;
	const char *const	home = get_var(getdata()->exported_env, "HOME");

	if (starts_with(path, home))
		ps1 = concatstr(4, "PS1=", "~", path + strln(home), " $ ");
	else
		ps1 = concatstr(3, "PS1=", path, " $ ");
	if (!ps1)
		return ;
	(getdata())->local_env = update_env(getdata()->local_env, ps1);
	free(ps1);
}

int	update_oldpwd(char **envp)
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

int	update_pwd(char **envp)
{
	char	*path;
	char	*pwd;

	path = getcwd(NULL, 0);
	updateps1(path);
	pwd = concatstr(2, "PWD=", path);
	free(path);
	if (!pwd)
		return (ERROR);
	envp = update_env(envp, pwd);
	free(pwd);
	if (!envp)
		return (ERROR);
	return (SUCCESS);
}
