/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:18 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/24 15:02:47 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include "data.h"
#include "env.h"
#include "util/util.h"

char	*displayprompt(void)
{
	char	*line;

	if (!(getdata()->isinteractive))
	{
		line = readline("");
		rl_already_prompted = 0;
		return (line);
	}
	rl_already_prompted = 0;
	line = readline(get_var(getdata()->local_env, "PS1"));
	return (line);
}
