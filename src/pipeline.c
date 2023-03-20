/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:46:35 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 17:54:53 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "builtins/builtins.h"
#include "parser/cmd.h"
#include "pipeline.h"
#include "redir.h"
#include "error.h"
#include "path.h"
#include "def.h"
#include "env.h"

struct s_exec_cmd_error
{
	t_cmd	*cmd;
	t_pipe	*prev_pipe;
	t_pipe	*next_pipe;
	char	*path;
};

static void	exec_cmd_error(struct s_exec_cmd_error var)
{
	print_error(var.path);
	free(var.path);
	if (var.prev_pipe)
		close_pipe(var.prev_pipe);
	if (!is_pipeline_end(var.cmd))
		close_pipe(var.next_pipe);	
}

// deal with cmd not found
static int	exec_cmd(t_cmd *cmd, t_pipe *prev_pipe, t_pipe *next_pipe)
{
	char	*path;
	
	if (prev_pipe)
		read_pipe(prev_pipe);
	if (!is_pipeline_end(cmd))
		write_pipe(next_pipe);
	dup2(cmd->io.read, STDIN_FILENO);
	dup2(cmd->io.write, STDOUT_FILENO);
	if (is_builtin(cmd))
		return (exec_builtin(cmd));
	path = resolve_exec_path(cmd->argv[0]);
	execve(path, cmd->argv, *(get_exported_env()));
	exec_cmd_error((struct s_exec_cmd_error){.cmd = cmd,
		.prev_pipe = prev_pipe, .next_pipe = next_pipe, .path = path});
	return (ERROR);
}

int	pipeline(t_cmd *cmd, t_pipe *prev_pipe)
{
	pid_t	cmd_pid;
	t_pipe	next_pipe;
	int		res;

	if (!is_pipeline_end(cmd)
		&& pipe(&next_pipe.read) == ERROR)
		return (ERROR);
	// les redirections sont faites avant le fork pour que le main process
	// puisse fermer les fichiers lorsque le child a terminé
	// Il serait bon que open_in/out ferme le pipe s'il y a lieu
	cmd->io.read = open_input(cmd->redirin);
	cmd->io.write = open_output(cmd->redirout);
	cmd_pid = fork();
	if (cmd_pid == 0
		&& exec_cmd(cmd, prev_pipe, &next_pipe) == ERROR)
		exit(EXIT_FAILURE);
	if (prev_pipe)
		close_pipe(prev_pipe);
	res = SUCCESS;
	if (!is_pipeline_end(cmd))
		res = pipeline(cmd->pipecmd, &next_pipe);
	return (res);
}
