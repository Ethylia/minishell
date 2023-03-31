/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:29:19 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/31 10:14:54 by francoma         ###   ########.fr       */
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
	i = -1;
	while (++i < cmd->redirout.size)
		free(((t_redir *)(cmd->redirout.data))[i].str);
	free(cmd->redirout.data);
	return (0);
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
		free(cmd->redirin[i].str);
	free(cmd->redirin);
	i = -1;
	while (cmd->redirout && cmd->redirout[++i].type)
		free(cmd->redirout[i].str);
	free(cmd->redirout);
	cmd->argv = 0;
	cmd->redirin = 0;
	cmd->redirout = 0;
}
