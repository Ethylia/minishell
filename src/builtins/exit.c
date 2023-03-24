/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:11:02 by francoma          #+#    #+#             */
/*   Updated: 2023/03/24 14:14:53 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "readline_extra.h"
#include "env.h"
#include "data.h"
#include "error.h"
#include "util/util.h"

static int	is_digit(const char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_number(const char *str)
{
	if (*str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
		if (!is_digit(*str++))
			return (0);
	return (1);
}

static unsigned char	atouc(const char *str)
{
	unsigned char	res;
	int				sign;

	if (!str)
		return (EXIT_FAILURE);
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	res = 0;
	while (*str)
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (sign * res);
}

int	bi_exit(const int argc, char *const argv[], char **envp)
{
	const unsigned char	exit_status = atouc(get_var(getdata()->local_env, "?"));

	(void) envp;
	write(STDOUT_FILENO, "exit\n", 5);
	if (argc < 2)
	{
		freedata();
		exit(exit_status);
	}
	if (!is_number(argv[1]))
	{
		print_err2("exit", argv[1], "numeric argument required");
		freedata();
		exit(255);
	}
	if (argc > 2)
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		return (EXIT_FAILURE);
	}
	freedata();
	exit(atouc(argv[1]));
	return (0);
}
