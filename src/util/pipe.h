/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:11 by francoma          #+#    #+#             */
/*   Updated: 2023/03/24 08:59:37 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

typedef struct s_pipe
{
	union
	{
		int	pipe[2];
		struct
		{
			int	read;
			int	write;
		};	
	};
}	t_pipe;

void	close_pipe(t_pipe *pipe);

#endif
