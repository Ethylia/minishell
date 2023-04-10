/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:46:35 by francoma          #+#    #+#             */
/*   Updated: 2023/04/10 08:01:21 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // close
#include <signal.h>
#include "builtins/builtins.h"
#include "redir.h"
#include "error.h"
#include "path.h"
#include "def.h"
#include "env.h"
#include "data.h"
#include "util/util.h"

static void	endpipeline(int	cmd_pid, int *res)
{
	pid_t	pid;

	pid = waitpid(cmd_pid, res, 0);
	if (pid == -1)
		*res = 2;
	if (!WIFEXITED(*res) && *res == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	else if (WIFEXITED(*res))
		*res = WEXITSTATUS(*res);
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

static int	exec_cmd(t_cmd *cmd, t_pipe *next_pipe)
{
	char		*exec_path;
	const char	*p;

	if (redir_output(cmd, next_pipe) == ERROR)
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

int	pipeline(t_cmd *cmd, t_pipe *prev_pipe)
{
	pid_t	cmd_pid;
	t_pipe	next_pipe;
	int		res;

	if (cmd->pipecmd && pipe(next_pipe.pipe) == ERROR)
		return (ERROR);
	res = redir_input(cmd, prev_pipe);
	if (res == ERROR)
		return (ERROR);
	cmd_pid = fork();
	if (cmd_pid == 0 && res)
	{
		if (dup2(res, STDIN_FILENO) == ERROR)
			exitfree(1);
		close(res);
	}
	if (cmd_pid == 0 && !exec_cmd(cmd, &next_pipe))
		exitfree(1);
	if (prev_pipe)
		close_pipe(prev_pipe);
	if (cmd->pipecmd)
		res = pipeline(cmd->pipecmd, &next_pipe);
	else
		endpipeline(cmd_pid, &res);
	return (res);
}
