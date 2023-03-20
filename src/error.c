/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:51:16 by francoma          #+#    #+#             */
/*   Updated: 2023/03/20 09:45:31 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>	// strerror
#include <stdlib.h>	// free
#include <errno.h>	// errno
#include <unistd.h>	// write
#include "def.h"
#include "util/util.h"

void	print_error(const char *problem)
{
	char	*msg;

	msg = concatstr(6, NAME, ": ", problem, ": ", strerror(errno), "\n");
	write(STDERR_FILENO, msg, strln(msg));
	free(msg);
}

void	exit_error(const char *problem)
{
	print_error(problem);
	// free stuff
	exit(EXIT_FAILURE);
}
