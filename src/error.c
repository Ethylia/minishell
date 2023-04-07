/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:51:16 by francoma          #+#    #+#             */
/*   Updated: 2023/04/07 11:30:40 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>	// strerror
#include <stdlib.h>	// free
#include <errno.h>	// errno
#include <unistd.h>	// write
#include "def.h"
#include "data.h"
#include "util/util.h"

int	print_err(const char *problem)
{
	char	*msg;

	msg = concatstr(5, NAME": ", problem, ": ", strerror(errno), "\n");
	write(STDERR_FILENO, msg, strln(msg));
	free(msg);
	return (ERROR);
}

int	print_err2(const char *program, const char *val, const char *error)
{
	char	*msg;

	msg = concatstr(7, NAME": ", program, ": ", val, ": ", error, "\n");
	write(STDERR_FILENO, msg, strln(msg));
	free(msg);
	return (ERROR);
}

void	exit_error(const char *problem)
{
	print_err(problem);
	exitfree(EXIT_FAILURE);
}
