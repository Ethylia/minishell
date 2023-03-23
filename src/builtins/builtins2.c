/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:16:22 by francoma          #+#    #+#             */
/*   Updated: 2023/03/23 13:51:25 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// dup
#include "util/util.h"
#include "builtins.h"
#include "redir.h"
#include "def.h"
#include "data.h"
#include "env.h"

static int	get_argc(char *const argv[])
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

static t_pipe	backup_fd(void)
{
	t_pipe		fd_backup;			

	fd_backup.read = dup(STDIN_FILENO);
	fd_backup.write = dup(STDOUT_FILENO);
	return (fd_backup);
}

static void	recover_fd_backup(t_pipe fd_backup)
{
	dup2(fd_backup.write, STDOUT_FILENO);
	dup2(fd_backup.read, STDIN_FILENO);
}

static int	assignment(const char *str)
{
	if (get_var((getdata())->exported_env, str))
		update_env(&(getdata())->exported_env, str);
	else
		update_env(&(getdata())->local_env, str);
	return (SUCCESS);
}

int	exec_builtin(t_cmd *cmd)
{
	const char	**names;
	size_t		i;

	if (strchar(cmd->argv[0], '='))
		return (assignment(cmd->argv[0]));
	names = get_builtins_names();
	i = -1;
	while (names[++i])
	{
		if (strcmp(cmd->argv[0], names[i]) == 0)
		{
			if (get_builtin_func(i)(get_argc(cmd->argv),
				cmd->argv, getdata()->exported_env) == ERROR)
				return (ERROR);
			return (SUCCESS);
		}
	}
	return (ERROR);
}

int	exec_redir_builtin(t_cmd *cmd)
{
	t_pipe		fd_backup;
	int			res;

	fd_backup = backup_fd();
	if (redir_input(cmd, NULL) == ERROR
		|| redir_output(cmd, NULL) == ERROR)
		return (EXIT_FAILURE);
	res = exec_builtin(cmd);
	recover_fd_backup(fd_backup);
	return (res == ERROR);
}
