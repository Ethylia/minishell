/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:46:35 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 17:20:53 by francoma         ###   ########.fr       */
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
#include "path.h"

int	is_pipeline_end(t_cmd *cmd)
{
	return (cmd->pipecmd == NULL);
}

void	close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
}

void	read_pipe(t_pipe *p)
{
	close(p->write);
	dup2(p->read, STDIN_FILENO);
}

void	write_pipe(t_pipe *p)
{
	close(p->read);
	dup2(p->write, STDOUT_FILENO);
}
