/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:54:24 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 08:20:41 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "data.h"
#include "env.h"

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
	freecmd(&data->cmd);
}
