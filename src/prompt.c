/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:18 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/23 15:29:05 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "data.h"
#include "env.h"
#include "util/util.h"

void	displayprompt(void)
{
	if (getdata()->intflag == 0 && isatty(STDOUT_FILENO))
	{
		(getdata()->intflag) = 1;
		write(1, get_var(getdata()->local_env, "PS1"),
			strln(get_var(getdata()->local_env, "PS1")));
	}
}
