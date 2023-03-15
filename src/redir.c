/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:23:51 by francoma          #+#    #+#             */
/*   Updated: 2023/03/15 11:00:56 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "parser/cmd.h"
#include "error.h"
#include "def.h"

int	redir_input(char **redirin)
{
	size_t	i;
	int		fd;

	i = 0;
	while (redirin[i])
	{
		if (i)
			close(fd);
		fd = open(redirin[i], O_RDONLY);
		if (fd == ERROR)
		{
			print_error(redirin[i]);
			return (ERROR);
		}
		i++;
	}
	dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}

int	redir_output(char **redirout)
{
	size_t	i;
	int		fd;

	i = 0;
	while (redirout[i])
	{
		if (i)
			close(fd);
		fd = open(redirout[i], O_CREAT | O_WRONLY);
		if (fd == ERROR)
		{
			print_error(redirout[i]);
			return (ERROR);
		}
		i++;
	}
	dup2(fd, STDOUT_FILENO);
	return (SUCCESS);
}
