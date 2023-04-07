/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:46:35 by francoma          #+#    #+#             */
/*   Updated: 2023/04/07 13:00:49 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // close
#include "builtins/builtins.h"
#include "redir.h"
#include "error.h"
#include "path.h"
#include "def.h"
#include "env.h"
#include "data.h"
#include "util/util.h"

static void	close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
}

static void	exit_err(char *exec_path)
{
	if (exec_path)
		print_err(exec_path);
	free(exec_path);
	exitfree(EXIT_FAILURE);
}

static void	exit_notfound(char *exec_path)
{
	char	*msg;

	msg = concatstr(4, NAME, ": ", exec_path, ": command not found\n");
	free(exec_path);
	if (!msg)
		exitfree(EXIT_FAILURE);
	write(STDERR_FILENO, msg, strln(msg));
	free(msg);
	exitfree(127);
}

// cmd not found: currently displays "file or dir not found"
static int	exec_cmd(t_cmd *cmd, t_pipe *prev_pipe, t_pipe *next_pipe)
{
	char		*exec_path;
	const char	*p;
	const int	res = redir_input(cmd, prev_pipe);

	if (res == ERROR - 1)
		return (0);
	if (res == ERROR || redir_output(cmd, next_pipe) == ERROR)
		exit_err(NULL);
	if (is_builtin(cmd))
	{
		if (exec_builtin(cmd) == ERROR)
			exit_notfound(NULL);
		exitfree(EXIT_SUCCESS);
	}
	exec_path = resolve_exec_path(cmd->argv[0]);
	if (!exec_path)
		exit_err(NULL);
	execve(exec_path, cmd->argv, getdata()->exported_env);
	p = get_var(getdata()->local_env, "PATH");
	if (!p)
		p = get_var(getdata()->exported_env, "PATH");
	if (p && p[0] && !strchar(cmd->argv[0], '/'))
		exit_notfound(exec_path);
	exit_err(exec_path);
	return (1);
}
#include <stdio.h>
void	sigs(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "ppppp", 5);
		exit(255);
	}
}

int	pipeline(t_cmd *cmd, t_pipe *prev_pipe)
{
	pid_t	cmd_pid;
	t_pipe	next_pipe;
	int		res;

	if (cmd->pipecmd && pipe(next_pipe.pipe) == ERROR)
		return (ERROR);
	cmd_pid = fork();
	if (cmd_pid == 0)
		signal(SIGINT, sigs);
	if (cmd_pid == 0 && !exec_cmd(cmd, prev_pipe, &next_pipe))
		exitfree(255);
	if (prev_pipe)
		close_pipe(prev_pipe);
	if (cmd->pipecmd)
		res = pipeline(cmd->pipecmd, &next_pipe);
	else
	{
		waitpid(cmd_pid, &res, 0);
		if (!WIFEXITED(res) && res == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		else if (WIFEXITED(res))
			res = WEXITSTATUS(res);
	}
	return (res);
}
