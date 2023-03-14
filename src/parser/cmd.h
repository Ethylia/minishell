/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:33:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/14 16:26:00 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stddef.h>

# pragma pack(push, 4)
typedef struct s_pipe
{
	int	read;
	int write;
}	t_pipe;
# pragma pack(pop)

typedef struct s_cmd
{
	struct s_cmd	*pipe;
	char			*cmd;
	char			**redirin;
	char			**redirout;
}	t_cmd;

t_cmd	buildcmds(char *line);

#endif
