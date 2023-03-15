/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:33:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/15 14:21:28 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stddef.h>

typedef struct s_pipe
{
	int	read;
	int	write;
}	t_pipe;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char *const		*argv;
	char			**redirin;
	char			**redirout;
}	t_cmd;

t_cmd	buildcmds(char *line);

#endif
