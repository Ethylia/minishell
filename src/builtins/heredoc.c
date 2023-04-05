/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:29:26 by francoma          #+#    #+#             */
/*   Updated: 2023/04/05 11:06:07 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h> // free
#include <unistd.h> // pipe, close
#include "util/util.h"
#include "redir.h"
#include "data.h"
#include "def.h"

static void	sig_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	freedata();
	exit(128 + signo);
}

void	bi_heredoc2(t_pipe p, const char *eof)
{
	char	*line;

	close(p.read);
	while (1)
	{
		line = readline(HEREDOC_PS);
		if (!line || strcmp(line, eof) == 0)
			break ;
		write(p.write, line, strln(line));
		write(p.write, "\n", 1);
		free(line);
	}
	freedata();
	close(p.write);
	exit(EXIT_SUCCESS);
}

int	bi_heredoc(const char *eof)
{
	t_pipe	p;
	pid_t	pid;

	if (pipe(p.pipe) == ERROR)
		return (ERROR);
	getdata()->backup_fd = p;
	signal(SIGINT, sig_handler);
	pid = fork();
	if (pid != 0)
	{
		close(p.write);
		while (waitpid(pid, NULL, 0) != pid)
			;
		return (p.read);
	}
	bi_heredoc2(p, eof);
	return (NO_FILE);
}
