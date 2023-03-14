/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:17:23 by francoma          #+#    #+#             */
/*   Updated: 2023/03/14 10:28:26 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define ERROR -1
#define SUCCESS 0

// fork 1st, redir out, close in
// fork next, redir in out
// last, redir in, close out
// flags: pipeline first, pipeline last
int	make_pipe(int pipefd[2], int pid[2])
{
	if (pipe(pipefd) == ERROR)
		return (ERROR);
	pid[0] = fork();
	if (pid[0] == ERROR)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (ERROR);
	}
	else if (pid[0] == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		return (SUCCESS);
	}
	pid[1] = fork();
	if (pid[1] == ERROR)
	{
		kill(SIGKILL, pid[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		return (ERROR);
	}
	else if (pid[1] == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		return (SUCCESS);
	}
	return (SUCCESS);
}

int main(void)
{
	int pipefd[2];
	int pid[2];
	
	if (make_pipe(pipefd, pid) == ERROR)
		return (EXIT_FAILURE);
	if (pid[0] == 0)
	{
		if (execve("/bin/cat", (char *const []){"/bin/cat", NULL}, (char *const []){"", NULL})
			== ERROR)
		{
			kill(SIGKILL, pid[1]);
			return (EXIT_FAILURE);
		}
	}
	else if (pid[1] == 0)
	{
		if (execve("/usr/bin/grep", (char *const []){"/usr/bin/grep", "salut", NULL}, (char *const []){"", NULL})
			== ERROR)
		{
			kill(SIGKILL, pid[0]);
			return (EXIT_FAILURE);
		}
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (EXIT_SUCCESS);
}
