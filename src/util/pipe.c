/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:11 by francoma          #+#    #+#             */
/*   Updated: 2023/04/10 10:27:52 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

#include <unistd.h>

void	close_pipe(t_pipe *pipe)
{
	if (pipe->read != -1)
		close(pipe->read);
	if (pipe->write != -1)
		close(pipe->write);
}
