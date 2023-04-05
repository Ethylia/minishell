/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:54:24 by francoma          #+#    #+#             */
/*   Updated: 2023/04/05 10:48:20 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "env.h"
#include "def.h"
#include "readline_extra.h"

t_data	*getdata(void)
{
	static t_data	data;

	return (&data);
}

void	freedata(void)
{
	t_data *const	data = getdata();

	if (data->exported_env)
	{
		free_env(data->exported_env);
		data->exported_env = NULL;
	}
	if (data->local_env)
	{
		free_env(data->local_env);
		data->local_env = NULL;
	}
	if (data->tokens)
	{
		free(data->tokens);
		data->tokens = NULL;
	}
	freecmd(&data->cmd);
	rl_clear_history();
	if (data->backup_fd.read != NO_FILE)
		close(data->backup_fd.read);
	if (data->backup_fd.write != NO_FILE)
		close(data->backup_fd.write);
}
