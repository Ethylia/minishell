/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:33:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/15 14:30:03 by eboyce-n         ###   ########.fr       */
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
	char			**argv;
	char			**redirin;
	char			**redirout;
}	t_cmd;

// returns a pointer to the first command in the linked list
// returns NULL if there is no command
// remember to free the linked list
t_cmd	*buildcmd(char *line);
void	freecmd(t_cmd *cmd);

#endif
