/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:33:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/20 16:25:30 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stddef.h>

# include "token.h"

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
	struct s_cmd	*pipecmd;
}	t_cmd;

t_cmd	buildcmd(t_token *tokens);
void	freecmd(t_cmd *cmd);
int		toke(t_token *tokens, size_t *i, size_t *j);
int		pipeline(t_cmd *cmd, t_pipe *prev_pipe);

#endif
