/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:43:46 by francoma          #+#    #+#             */
/*   Updated: 2023/03/24 11:03:40 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "env.h"
#include "util/util.h"
#include "data.h"

#define ENV_PATH_SEP ':'
#define NO_RIGHTS 0000

static char	*find_in_path(char const *word, char const *env_path)
{
	char	*path;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (env_path[end])
	{
		if (end)
			start = end + 1;
		end = start;
		while (env_path[end] && env_path[end] != ENV_PATH_SEP)
			end++;
		if (env_path[end - 1] == '/')
			path = concatstr_ln(2, env_path + start, end - start, word,
					strln(word));
		else
			path = concatstr_ln(3, env_path + start, end - start, "/", 1, word,
					strln(word));
		if (access(path, NO_RIGHTS) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

static char	*copy_word(char *word)
{
	return (concatstr(1, word));
}

// Must free return
char	*resolve_exec_path(char *word)
{
	char const	*env_path;
	char		*exec_path;	

	if (strchar(word, '/'))
		return (copy_word(word));
	env_path = get_var(getdata()->exported_env, "PATH");
	if (!env_path)
		env_path = get_var(getdata()->local_env, "PATH");
	if (!env_path)
		return (copy_word(word));
	exec_path = find_in_path(word, env_path);
	if (!exec_path)
		return (copy_word(word));
	return (exec_path);
}
