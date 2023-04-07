/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:16:22 by francoma          #+#    #+#             */
/*   Updated: 2023/04/07 10:52:43 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// dup
#include <stdio.h> // perror
#include "util/util.h"
#include "builtins.h"
#include "redir.h"
#include "def.h"
#include "data.h"

static int	get_argc(char *const argv[])
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

static void	backup_fd(void)
{
	t_data *const	data = getdata();

	data->backup_fd.read = dup(STDIN_FILENO);
	data->backup_fd.write = dup(STDOUT_FILENO);
	if (data->backup_fd.read == ERROR
		|| data->backup_fd.write == ERROR)
	{
		freedata();
		perror("backup_fd\n");
		exit(EXIT_FAILURE);
	}
}

static void	recover_fd_backup(void)
{
	t_data *const	data = getdata();

	if (dup2(data->backup_fd.read, STDIN_FILENO) != STDIN_FILENO
		|| dup2(data->backup_fd.write, STDOUT_FILENO) != STDOUT_FILENO)
	{
		freedata();
		perror("recover_fd_backup\n");
		exit(EXIT_FAILURE);
	}
	close(data->backup_fd.read);
	close(data->backup_fd.write);
	data->backup_fd.read = NO_FILE;
	data->backup_fd.write = NO_FILE;
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
	int			res;

	backup_fd();
	res = redir_input(cmd, NULL);
	if (res == ERROR - 1)
		return (1);
	if (res == ERROR || redir_output(cmd, NULL) == ERROR)
		return (EXIT_FAILURE);
	res = exec_builtin(cmd);
	recover_fd_backup();
	return (res == ERROR);
}
