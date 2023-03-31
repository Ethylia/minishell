/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:15:18 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 09:04:12 by francoma         ###   ########.fr       */
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

static int	is_option(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i++] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static struct s_options	parse_option(char *const argv[])
{
	struct s_options	res;
	size_t				i;

	i = 1;
	res.end_nl = 1;
	res.arg_start = i;
	while (argv[i] && is_option(argv[i]))
	{
		res.end_nl = 0;
		res.arg_start = ++i;
	}
	return (res);
}

int	bi_echo(const int argc, char *const argv[], char **envp)
{
	struct s_options	opts;
	int					i;

	(void) envp;
	if (argc == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (SUCCESS);
	}
	opts = parse_option(argv);
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
