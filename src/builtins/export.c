/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:48:23 by francoma          #+#    #+#             */
/*   Updated: 2023/03/23 16:40:26 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../util/util.h"
#include "../env.h"
#include "../def.h"

int	assignment(const char *str)
{
	if (get_var((getdata())->exported_env, str))
		update_env(&(getdata())->exported_env, str);
	else
		update_env(&(getdata())->local_env, str);
	return (SUCCESS);
}

int	bi_export(const int argc, char *const argv[], char **envp)
{
	(void) envp;
	if (argc < 2)
		return (ERROR);
	if (get_var((getdata())->local_env, argv[1]))
	{
		if (strchar(argv[1], '='))
			update_env(&(getdata())->exported_env, argv[1]);
		else
			update_env(&(getdata())->exported_env, get_var((getdata())->local_env, argv[1]));
		rm_env(&((getdata())->local_env), argv[1]);
	}
	else if (strchar(argv[1], '='))
		update_env(&(getdata())->exported_env, argv[1]);
	if (!(getdata())->exported_env || !(getdata())->local_env)
		return (ERROR);
	return (SUCCESS);
}
