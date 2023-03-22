/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:48:23 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 16:53:23 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../util/util.h"
#include "../env.h"
#include "../def.h"

int	bi_export(const int argc, char *const argv[], char **envp)
{
	if (argc < 2)
		return (ERROR);
	if (get_var((getdata())->local_env, argv[1]))
	{
		if (strchar(argv[1], '='))
			update_env(&envp, argv[1]);
		else
			update_env(&envp, get_var((getdata())->local_env, argv[1]));
		rm_env(&((getdata())->local_env), argv[1]);
	}
	else if (strchar(argv[1], '='))
		update_env(&envp, argv[1]);
	if (!envp || !(getdata())->local_env)
		return (ERROR);
	return (SUCCESS);
}
