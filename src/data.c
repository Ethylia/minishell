/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:54:24 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 09:36:34 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "env.h"
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
}
