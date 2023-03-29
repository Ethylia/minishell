/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:33:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/29 14:56:10 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stddef.h>
# include "token.h"
# include "util/vector.h"

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

enum e_OP
{
	OP_NONE,
	OP_PIPE,
	OP_AND,
	OP_OR
};

typedef struct s_redir
{
	char			*str;
	enum e_tokens	type;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirout;
	t_redir			*redirin;
	struct s_cmd	*pipecmd;
}	t_cmd;

typedef struct s_counts
{
	size_t	argc;
	size_t	redirin;
	size_t	redirout;
}	t_counts;

typedef struct s_cmdvec
{
	t_vector	argv;
	t_vector	redirin;
	t_vector	redirout;
}	t_cmdvec;

int		buildcmd(t_token *tokens, t_cmd *cmd);
int		freecmdvec(t_cmdvec *cmd);
void	freecmd(t_cmd *cmd);
int		toke(t_token *tokens, size_t *i, size_t *j);
size_t	buildtd(t_vector *argv, t_vector *arg, t_token *token);
size_t	buildwrd(t_cmdvec *cmd, t_token *tokens, size_t i);
size_t	buildredir(t_cmdvec *cmd, t_token *tokens, size_t i);

#endif
