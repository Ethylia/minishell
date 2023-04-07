/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:29:26 by francoma          #+#    #+#             */
/*   Updated: 2023/04/07 11:32:46 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h> // free
#include <unistd.h> // pipe, close
#include "prompt.h"
#include "util/util.h"
#include "redir.h"
#include "data.h"
#include "def.h"
#include "env.h"

static void	sig_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	exitfree(128 + signo);
}

static size_t	tdlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && gettoken(s + i) == twrd && s[i] != '/' && s[i] != '*'
		&& s[i] != '?' && s[i] != '=')
		i++;
	return (i);
}

size_t	writeline(const char *line, int quoted)
{
	size_t		i;
	const char	*var;

	if (*line == '$' && !quoted)
	{
		var = get_varn(getdata()->exported_env, line + 1, tdlen(line + 1));
		if (!var)
			get_varn(getdata()->local_env, line + 1, tdlen(line + 1));
		if (var)
			write(getdata()->backup_fd.write, var, strln(var));
		return (tdlen(line + 1) + 1);
	}
	i = 0;
	while (line[i] && (line[i] != '$' || quoted))
		i++;
	write(getdata()->backup_fd.write, line, i);
	return (i);
}

void	bi_heredoc2(t_pipe p, const char *eof, int quoted)
{
	char	*line;
	size_t	i;

	close(p.read);
	while (1)
	{
		togglectl(0);
		line = readline(HEREDOC_PS);
		togglectl(1);
		if (!line || strcmp(line, eof) == 0)
			break ;
		i = 0;
		while (line[i])
			i += writeline(line + i, quoted);
		write(p.write, "\n", 1);
		free(line);
	}
	close(p.write);
	exitfree(EXIT_SUCCESS);
}

int	bi_heredoc(const char *eof, int quoted)
{
	t_pipe	p;
	pid_t	pid;
	int		status;

	if (pipe(p.pipe) == ERROR)
		return (ERROR);
	pid = fork();
	if (pid != 0)
	{
		close(p.write);
		while (waitpid(pid, &status, 0) != pid)
			;
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
			return (p.read);
		else
		{
			close(p.read);
			return (ERROR - 1);
		}
	}
	signal(SIGINT, sig_handler);
	getdata()->backup_fd = p;
	bi_heredoc2(p, eof, quoted);
	return (NO_FILE);
}
