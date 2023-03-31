/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_extra2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:54:36 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 17:01:38 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/vector.h"
#include "env.h"
#include "data.h"
#include "util/util.h"
#include <dirent.h>
#include <sys/stat.h>

typedef struct s_path
{
	char			*s;
	size_t			c;
	DIR				*folder;
	struct dirent	*file;	
}	t_path;

static char const	*get_env_path(void)
{
	char const *const	env_path = get_var(getdata()->exported_env, "PATH");

	if (!env_path)
		return (get_var(getdata()->local_env, "PATH"));
	return (env_path);
}

static t_path	split_path(void)
{
	t_path		path;
	char		*tmp;

	path.s = strdupe(get_env_path());
	tmp = path.s;
	path.c = !!tmp;
	while (tmp)
	{
		tmp = strchar(tmp, ':');
		if (tmp)
		{
			*tmp = '\0';
			++tmp;
			++path.c;
		}
	}
	return (path);
}

static int	is_executable(const char *basename, const char *dir)
{
	struct stat	buf;
	char		*path;
	int			res;

	res = 0;
	path = concatstr(3, dir, "/", basename);
	if (stat(path, &buf) == 0
		&& S_ISREG(buf.st_mode) && (buf.st_mode & S_IXUSR))
		res = 1;
	free(path);
	return (res);
}

static void	get_path_executables2(t_path *path,
	t_vector *vec, const char *s, int p)
{
	size_t		i;
	char		*tmp;

	tmp = path->s;
	i = -1;
	while (++i < path->c)
	{
		path->folder = opendir(tmp);
		if (!path->folder)
			break ;
		while (1)
		{
			path->file = readdir(path->folder);
			if (!path->file)
				break ;
			if (!is_executable(path->file->d_name, tmp)
				|| strncmp(path->file->d_name, s, p))
				continue ;
			v_pushelem(vec, strdupe(path->file->d_name));
		}
		tmp = strchar(tmp, '\0') + 1;
		closedir(path->folder);
	}
}

void	get_path_executables(const char *s, int p, t_vector *vec)
{
	t_path	path;

	path = split_path();
	get_path_executables2(&path, vec, s, p);
	free(path.s);
}
