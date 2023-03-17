/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:29:19 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/17 11:26:11 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

#include "util/util.h"

t_cmd	buildcmd(char *line)
{
	t_cmd	cmd;

	
	return (cmd);
}

void	freecmd(t_cmd *cmd)
{
	size_t	i;

	i = -1;
	while (cmd->argv[++i])
		free(cmd->argv[i]);
	free(cmd->argv);
	i = -1;
	while (cmd->redirin[++i])
		free(cmd->redirin[i]);
	free(cmd->redirin);
	i = -1;
	while (cmd->redirout[++i])
		free(cmd->redirout[i]);
	free(cmd->redirout);
}
