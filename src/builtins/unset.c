/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:30:37 by francoma          #+#    #+#             */
/*   Updated: 2023/03/22 16:40:00 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../util/util.h"
#include "../env.h"
#include "../def.h"

int	bi_unset(const int argc, char *const argv[], char **envp)
{
	(void) argv;
	(void) envp;
	if (argc < 2)
		return (ERROR);
	rm_env(&((getdata())->local_env), argv[1]);
	rm_env(&envp, argv[1]);
	return (SUCCESS);
}
