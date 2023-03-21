/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:46:35 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 15:42:50 by francoma         ###   ########.fr       */
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
