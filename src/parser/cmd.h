/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:33:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/16 13:10:46 by eboyce-n         ###   ########.fr       */
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

enum e_OP
{
	OP_NONE,
	OP_PIPE,
	OP_AND,
	OP_OR
};

typedef struct s_cmd
{
	char			**argv;
	char			**redirin;
	char			**redirout;
}	t_cmd;

typdef struct s_cmdtree
{
	struct s_cmdtree	*next;
	struct s_cmdtree	*nodes;
	t_cmd				*cmd;
	int					op;
}	t_cmdtree;

// returns a pointer to the first command in the linked list
// returns NULL if there is no command
// remember to free the linked list
t_cmdtree	*buildcmd(char *line);
void		freecmd(t_cmdtree *cmd);

#endif
