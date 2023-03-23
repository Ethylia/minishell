/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:18 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/23 16:01:11 by eboyce-n         ###   ########.fr       */
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
	(getdata()->intflag) = 1;
	return (readline(get_var(getdata()->local_env, "PS1")));
	(getdata()->intflag) = 0;
}
