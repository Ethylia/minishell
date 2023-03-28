/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:38:33 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/28 17:15:05 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/util.h"
#include "util/vector.h"
#include "cmd.h"
#include "env.h"
#include "data.h"

#define NULLPTR "\0\0\0\0\0\0\0\0"

static void	initcmdvec(t_cmdvec *cmd)
{
	v_init(&cmd->argv, sizeof(char *), 8);
	v_init(&cmd->redirin, sizeof(t_redir), 4);
	v_init(&cmd->redirout, sizeof(t_redir), 4);
}

static void	initcmd(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->redirin = NULL;
	cmd->redirout = NULL;
	cmd->pipecmd = NULL;
}

// static size_t	buildredir(t_cmd *cmd, t_token *tokens, size_t i)
// {
// 	t_redir		redir;
// 	t_vector	arg;

// 	redir.type = tokens[i].type;
// 	return (i + 2);
// }

static int	buildcmd2(t_cmdvec *vec, t_token *tokens, t_cmd *cmd, size_t i)
{
	while (tokens[i].type)
	{
		if (tokens[i].type & (twrd | td | tqts | tdqts))
			i = buildwrd(vec, tokens, i);
		// else if (tokens[i].type & (tdin | tdout | tapp))
		// 	i = buildredir(vec, tokens, i);
		else if (tokens[i].type & (tpipe))
		{
			cmd->pipecmd = malloc(sizeof(t_cmd));
			if (!buildcmd(tokens + i + 1, cmd->pipecmd))
			{
				freecmdvec(vec);
				return (0);
			}
			break ;
		}
		else if (tokens[i].type & (tand | tor))
			break ;
		else
			++i;
	}
	return (1);
}

int	buildcmd(t_token *tokens, t_cmd *cmd)
{
	int				ret;
	t_cmdvec		vec;
	const t_redir	nullredir = {0, 0};

	if (!cmd)
		return (0);
	initcmd(cmd);
	initcmdvec(&vec);
	ret = buildcmd2(&vec, tokens, cmd, 0);
	if (ret)
	{
		v_push(&vec.argv, NULLPTR);
		v_push(&vec.redirin, &nullredir);
		v_push(&vec.redirout, &nullredir);
		cmd->argv = (char **)vec.argv.data;
		cmd->redirin = (t_redir *)vec.redirin.data;
		cmd->redirout = (t_redir *)vec.redirout.data;
	}
	freecmdvec(&vec);
	return (ret);
}
