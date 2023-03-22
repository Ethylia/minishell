/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:46:35 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 15:45:27 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "builtins/builtins.h"
#include "parser/cmd.h"
#include "pipeline.h"
#include "redir.h"
#include "error.h"
#include "path.h"
#include "def.h"
#include "env.h"
#include "sig.h"

static void	close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
}

static int	exit_err(char *exec_path)
{
	print_err(exec_path);
	free(exec_path);
	return (ERROR);
}

// static int	exit_success(char *exec_path)
// {
// 	free(exec_path);
// 	return (SUCCESS);
// }

// cmd not found: currently displays "file or dir not found"
static int	exec_cmd(t_cmd *cmd, t_pipe *prev_pipe, t_pipe *next_pipe)
{
	char	*exec_path;

	if (redir_input(cmd, prev_pipe) == ERROR
		|| redir_output(cmd, next_pipe) == ERROR)
		return(exit_err(NULL));
	if (is_builtin(cmd))
	{
		if (exec_builtin(cmd) == ERROR)
			return(exit_err(NULL));
		exit(EXIT_SUCCESS);
	}
	exec_path = resolve_exec_path(cmd->argv[0]);
	if (!exec_path)
		return(exit_err(NULL));
	execve(exec_path, cmd->argv, *(get_exported_env()));
	return(exit_err(exec_path));
}
 
int	pipeline(t_cmd *cmd, t_pipe *prev_pipe)
{
	pid_t	cmd_pid;
	t_pipe	next_pipe;
	int		res;

	if (cmd->pipecmd && pipe(next_pipe.pipe) == ERROR)
		return (ERROR);
	cmd_pid = fork();
	if (cmd_pid == 0 && exec_cmd(cmd, prev_pipe, &next_pipe) == ERROR)
		exit(EXIT_FAILURE);
	if (prev_pipe)
		close_pipe(prev_pipe);
	if (cmd->pipecmd)
		res = pipeline(cmd->pipecmd, &next_pipe);
	else
	{
		waitpid(cmd_pid, &res, 0);
		if (WIFEXITED(res))
			res = WEXITSTATUS(res);
		if (*getquitflag() == 1 && res == 3)
		{
			*getquitflag() = 0;
			printf("Quit: 3\n");
		}
	}
	return (res);
}
