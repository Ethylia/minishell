/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:33:44 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/27 15:56:26 by eboyce-n         ###   ########.fr       */
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
	t_vector		argv;
	t_vector		redirout;
	t_vector		redirin;
	struct s_cmd	*pipecmd;
}	t_cmd;

typedef struct s_counts
{
	size_t	argc;
	size_t	redirin;
	size_t	redirout;
}	t_counts;

typedef struct s_cmdgroup
{
	t_cmd		cmd;
	size_t		i[2];
	t_counts	c[2];
}	t_cmdgroup;

int		buildcmd(t_token *tokens, t_cmd *cmd);
void	freecmd(t_cmd *cmd);
int		toke(t_token *tokens, size_t *i, size_t *j);
void	buildpipe(t_cmd *cmd, t_token *tokens);
void	setredir(t_cmdgroup *g, enum e_tokens type, t_token *tokens, size_t i);
void	buildarg(t_cmdgroup *g, t_token *tokens, size_t i);

#endif
