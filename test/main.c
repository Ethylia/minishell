/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:30:34 by francoma          #+#    #+#             */
/*   Updated: 2023/03/14 16:24:49 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include "../src/parser/cmd.h"

#define ERROR -1
#define SUCCESS 0
#define NUM_CMD 3

typedef struct s_cmd
{
	pid_t		pid;
	const char	*path;
	char *const	*argv;
}	t_cmd;

static int	is_pipeline_start(t_pipe *ppipefd)
{
	return (ppipefd == NULL);
}

static int	is_pipeline_end(t_cmd *cmds)
{
	return (cmds[1].path == NULL);
}

int	make_pipe(t_pipe *ppipefd, t_cmd *cmds)
{
	t_pipe	pipefd;
	int		res;
	
	res = SUCCESS;
	if (!is_pipeline_end(cmds)
		&& pipe(&pipefd.read) == ERROR)
		return (ERROR);
	cmds[0].pid = fork();
	if (cmds[0].pid == 0)
	{
		if (!is_pipeline_start(ppipefd))
		{
			close(ppipefd->write);
			dup2(ppipefd->read, STDIN_FILENO);
		}			
		if (!is_pipeline_end(cmds))
		{
			close(pipefd.read);
			dup2(pipefd.write, STDOUT_FILENO);
		}
		return (execve(cmds[0].path, cmds[0].argv, NULL));
	}
	if (!is_pipeline_end(cmds))
		res = make_pipe(&pipefd, cmds + 1);
	close(pipefd.read);
	close(pipefd.write);
	return (res);
}

int main(void)
{
	t_cmd	cmds[3];
	
	cmds[0] = (t_cmd){.path = "/bin/cat", .argv = (char *const []){"/bin/cat", NULL}};
	cmds[1] = (t_cmd){.path = "/usr/bin/grep", .argv = (char *const []){"/usr/bin/grep", "salut", NULL}};
	cmds[2] = (t_cmd){.path = NULL};
	if (make_pipe(NULL, cmds) == ERROR)
		return (EXIT_FAILURE);
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (EXIT_SUCCESS);
}
