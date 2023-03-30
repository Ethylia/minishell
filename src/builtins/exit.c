/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:11:02 by francoma          #+#    #+#             */
/*   Updated: 2023/03/30 09:05:27 by francoma         ###   ########.fr       */
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
#include "def.h"

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
	if (!is_number(argv[1]))
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
