/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:31:49 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 15:08:22 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../util/util.h"
#include "../def.h"
#include "../env.h"
#include "data.h"

void	updateps1(const char *path)
{
	char				*ps1;
	const char *const	home = get_var(getdata()->exported_env, "HOME");

	if (home)
	{
		if (starts_with(path, home))
			ps1 = concatstr(4, "PS1=", "~", path + strln(home), " $ ");
		else
			ps1 = concatstr(3, "PS1=", path, " $ ");
	}
	else
		ps1 = concatstr(3, "PS1=", path, " $ ");
	if (!ps1)
		return ;
	update_env(&(getdata()->local_env), ps1);
	free(ps1);
}

int	update_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = concatstr(2, "OLDPWD=", get_var(getdata()->exported_env, "PWD"));
	if (!oldpwd)
		return (ERROR);
	update_env(&(getdata()->exported_env), oldpwd);
	free(oldpwd);
	return (SUCCESS);
}

int	update_pwd(void)
{
	char	*path;
	char	*pwd;

	path = getcwd(NULL, 0);
	updateps1(path);
	pwd = concatstr(2, "PWD=", path);
	free(path);
	if (!pwd)
		return (ERROR);
	update_env(&(getdata()->exported_env), pwd);
	free(pwd);
	return (SUCCESS);
}
