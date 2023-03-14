/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:30:34 by francoma          #+#    #+#             */
/*   Updated: 2023/03/14 15:43:45 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#define ERROR -1
#define SUCCESS 0
#define NUM_CMD 3

typedef struct s_cmd
{
	pid_t		pid;
	const char	*path;
	char *const	*argv;
}	t_cmd;

static int	is_pipeline_start(int *ppipefd)
{
	return (ppipefd == NULL);
}

static int	is_pipeline_end(t_cmd *cmds)
{
	return (cmds[1].path == NULL);
}

int	make_pipe(int ppipefd[2], t_cmd *cmds)
{
	int	pipefd[2];
	
	if (!is_pipeline_end(cmds)
		&& pipe(pipefd) == ERROR)
		return (ERROR);
	cmds[0].pid = fork();
	if (cmds[0].pid == 0)
	{
		if (!is_pipeline_start(ppipefd))
		{
			close(ppipefd[1]);
			dup2(ppipefd[0], STDIN_FILENO);
		}			
		if (!is_pipeline_end(cmds))
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
		}
		execve(cmds[0].path, cmds[0].argv, NULL);
		return (ERROR);
	}
	if (!is_pipeline_end(cmds))
		return (make_pipe(pipefd, cmds + 1));
	return (SUCCESS);
}

int main(void)
{
	t_cmd	cmds[3];
	
	cmds[0] = (t_cmd){.path = "/bin/cat", .argv = (char *const []){"/bin/cat", NULL}};
	cmds[1] = (t_cmd){.path = "/usr/bin/grep", .argv = (char *const []){"/usr/bin/grep", "salut", NULL}};
	cmds[2] = (t_cmd){.path = NULL};
	if (make_pipe(NULL, cmds) == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
