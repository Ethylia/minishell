/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:23:51 by francoma          #+#    #+#             */
/*   Updated: 2023/03/21 15:44:57 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "builtins/builtins.h"
#include "parser/token.h"
#include "parser/cmd.h"
#include "pipeline.h"
#include "error.h"
#include "redir.h"
#include "def.h"

static int	handle_prev_pipe(t_pipe *prev_pipe)
{
	if (prev_pipe)
	{
		close(prev_pipe->write);
		return (prev_pipe->read);
	}
	return (NO_FILE);
}

int	redir_input(t_cmd *cmd, t_pipe *prev_pipe)
{
	size_t	i;
	int		fd;

	fd = handle_prev_pipe(prev_pipe);
	i = 0;
	while (cmd->redirin[i].str)
	{
		if (fd != NO_FILE)
			close(fd);
		if (cmd->redirin[i].type & tdin)
			fd = open(cmd->redirin[i].str, O_RDONLY);
		else
			fd = bi_heredoc(cmd->redirin[i].str);
		if (fd == ERROR)
		{
			print_err(cmd->redirin[i].str);
			return (ERROR);
		}
		i++;
	}
	if (fd == NO_FILE)
		return (SUCCESS);
	if (dup2(fd, STDIN_FILENO) == ERROR)
		return (ERROR);
	close(fd);
	return (SUCCESS);
}

static int	handle_next_pipe(t_cmd *cmd, t_pipe *next_pipe)
{
	if (!is_pipeline_end(cmd))
	{
		close(next_pipe->read);
		return (next_pipe->write);
	}
	return (NO_FILE);
}

static int	get_flags(t_redir *redir)
{
	if (redir->type == tdout)
		return (O_CREAT | O_WRONLY);
	return (O_APPEND | O_WRONLY);
}

int	redir_output(t_cmd *cmd, t_pipe *next_pipe)
{
	size_t	i;
	int		fd;

	fd = handle_next_pipe(cmd, next_pipe);
	i = 0;
	while (cmd->redirout[i].str)
	{
		if (fd != NO_FILE)
			close(fd);
		fd = open(cmd->redirout[i].str,
			get_flags(&cmd->redirout[i]), REDIROUT_MODE);
		if (fd == ERROR)
		{
			print_err(cmd->redirout[i].str);
			return (ERROR);
		}
		i++;
	}
	if (fd != NO_FILE)
	{
		if (dup2(fd, STDOUT_FILENO) == ERROR)
			return (ERROR);
		close(fd);
	}
	return (SUCCESS);
}
