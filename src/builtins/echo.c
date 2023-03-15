/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:15:18 by francoma          #+#    #+#             */
/*   Updated: 2023/03/15 13:11:24 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// STDOUT_FILENO
#include "../util/util.h"
#include "../def.h"

struct s_options
{
	int	end_nl;
	int	arg_start;
};

static struct s_options	parse_option(char *option)
{
	struct s_options	res;

	if (strcmp(option, "-n") == 0)
	{
		res.arg_start = 2;
		res.end_nl = 0;
	}
	else
	{
		res.arg_start = 1;
		res.end_nl = 1;
	}
	return (res);
}

int	echo(const int argc, char *const argv[], char *const envp[])
{
	struct s_options	opts;
	int					i;

	(void) envp;
	if (argc == 1)
		return (SUCCESS);
	opts = parse_option(argv[1]);
	i = opts.arg_start;
	while (i < argc)
	{
		write(STDOUT_FILENO, argv[i], strln(argv[i]));
		if (i < argc - 1)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (opts.end_nl)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
