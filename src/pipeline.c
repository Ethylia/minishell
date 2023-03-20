/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:46:35 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 16:52:17 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "builtins/builtins.h"
#include "parser/cmd.h"
#include "def.h"
#include "redir.h"
#include "env.h"

static int	is_pipeline_end(t_cmd *cmd)
{
	return (cmd->pipecmd == NULL);
}

static void	close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
}

static void	read_pipe(t_pipe *p)
{
	close(p->write);
	dup2(p->read, STDIN_FILENO);
}

static void	write_pipe(t_pipe *p)
{
	close(p->read);
	dup2(p->write, STDOUT_FILENO);
}

// deal with cmd not found
static int	exec_cmd(t_cmd *cmd, t_pipe *prev_pipe, t_pipe *next_pipe)
{
	if (prev_pipe)
		read_pipe(prev_pipe);
	if (!is_pipeline_end(cmd))
		write_pipe(next_pipe);
	redir_input(cmd->redirin);
	redir_output(cmd->redirout);
	if (is_builtin(cmd))
		return (exec_builtin(cmd));
	return (execve(cmd->argv[0], cmd->argv, *(get_exported_env())));
}

int	pipeline(t_cmd *cmd, t_pipe *prev_pipe)
{
	pid_t	cmd_pid;
	t_pipe	next_pipe;
	int		res;

	if (!is_pipeline_end(cmd)
		&& pipe(&next_pipe.read) == ERROR)
		return (ERROR);
	cmd_pid = fork();
	if (cmd_pid == 0
		&& exec_cmd(cmd, prev_pipe, &next_pipe) == ERROR)
	{
		if (prev_pipe)
			close_pipe(prev_pipe);
		if (!is_pipeline_end(cmd))
			close_pipe(&next_pipe);
		exit(EXIT_FAILURE);
	}
	if (prev_pipe)
		close_pipe(prev_pipe);
	res = SUCCESS;
	if (!is_pipeline_end(cmd))
		res = pipeline(cmd->pipecmd, &next_pipe);
	return (res);
}
