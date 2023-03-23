/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:30:37 by francoma          #+#    #+#             */
/*   Updated: 2023/03/23 16:50:20 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "data.h"
#include "util/util.h"
#include "env.h"
#include "def.h"

static void	print_er(const char *str)
{
	const size_t	l = strln_del(str, '=');

	write(STDERR_FILENO, "minishell: unset: `", 19);
	write(STDERR_FILENO, str, l);
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}

int	bi_unset(const int argc, char *const argv[], char **envp)
{
	(void) argv;
	(void) envp;
	if (argc < 2)
		return (ERROR);
	if (!isalphaunder(argv[1][0]) || !stralphanumunder(argv[1]))
	{
		print_er(argv[1]);
		return (ERROR);
	}
	rm_env(&((getdata())->local_env), argv[1]);
	rm_env(&((getdata())->exported_env), argv[1]);
	return (SUCCESS);
}
