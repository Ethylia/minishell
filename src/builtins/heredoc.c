/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:29:26 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 11:58:13 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../parser/cmd.h"
#include "../util/util.h"
#include "../redir.h"
#include "../def.h"

int	bi_heredoc(const char *eof)
{
	char	*line;
	t_pipe	p;

	if (pipe(p.pipe) == ERROR)
		return (ERROR);
	while (1)
	{
		line = readline(HEREDOC_PS);
		if (!line || strcmp(line, eof) == 0)
			break ;
		write(p.write, line, strln(line));
		write(p.write, "\n", 1);
		free(line);
	}
	close(p.write);
	return (p.read);
}
