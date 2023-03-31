/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:11:02 by francoma          #+#    #+#             */
/*   Updated: 2023/03/31 09:10:13 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "data.h"
#include "error.h"
#include "util/util.h"
#include "def.h"

static int	is_digit(const char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_long_long(const char *str)
{
	size_t	sl;
	int		n;
	int		z;

	sl = 0;
	n = 0;
	while (is_ws(*str))
		++str;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			n = !n;
	z = 0;
	if (*str == '0')
		z = 1;
	while (*str == '0')
		++str;
	while (is_digit(str[sl]))
		++sl;
	if (sl > 19 || (!sl && !z) || (!!str[sl]))
		return (0);
	if (sl == 19)
		if ((!n && strcmp(str, "9223372036854775807") > 0)
			|| (n && strcmp(str, "9223372036854775808") > 0))
			return (0);
	return (1);
}

int	bi_exit(const int argc, char *const argv[],
	__attribute__((unused))char **envp)
{
	const unsigned char	exit_status = atouc(get_var(getdata()->local_env, "?"));
	unsigned char		e;

	if (getdata()->isinteractive)
		write(STDERR_FILENO, "exit\n", 5);
	if (argc < 2)
	{
		freedata();
		exit(exit_status);
	}
	if (!is_long_long(argv[1]))
	{
		print_err2("exit", argv[1], "numeric argument required");
		freedata();
		exit(255);
	}
	if (argc > 2)
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		return (ERROR);
	}
	e = atouc(argv[1]);
	freedata();
	exit(e);
	return (0);
}
