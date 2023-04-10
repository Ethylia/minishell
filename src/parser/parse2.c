/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:29:19 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/10 09:26:20 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "util/util.h"

int	freecmdvec(t_cmdvec *cmd)
{
	size_t	i;

	v_free_elems(&cmd->argv);
	i = -1;
	while (++i < cmd->redirin.size)
		free(((t_redir *)(cmd->redirin.data))[i].str);
	free(cmd->redirin.data);
	cmd->redirin.data = 0;
	cmd->redirin.size = 0;
	i = -1;
	while (++i < cmd->redirout.size)
		free(((t_redir *)(cmd->redirout.data))[i].str);
	free(cmd->redirout.data);
	cmd->redirout.data = 0;
	cmd->redirout.size = 0;
	return (0);
}

void	freecmd2(t_redir *redir)
{
	if (redir->type == thdoc)
		if (redir->fd > 2)
			close(redir->fd);
	free(redir->str);
}

void	freecmd(t_cmd *cmd)
{
	size_t	i;

	if (cmd->pipecmd)
	{
		freecmd(cmd->pipecmd);
		free(cmd->pipecmd);
	}
	cmd->pipecmd = 0;
	i = -1;
	while (cmd->argv && cmd->argv[++i])
		free(cmd->argv[i]);
	free(cmd->argv);
	i = -1;
	while (cmd->redirin && cmd->redirin[++i].type)
		freecmd2(&cmd->redirin[i]);
	free(cmd->redirin);
	i = -1;
	while (cmd->redirout && cmd->redirout[++i].type)
		free(cmd->redirout[i].str);
	free(cmd->redirout);
	cmd->argv = 0;
	cmd->redirin = 0;
	cmd->redirout = 0;
}
