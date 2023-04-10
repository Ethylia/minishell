/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:38:33 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/10 08:30:35 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "util/util.h"
#include "util/vector.h"
#include "builtins/builtins.h"
#include "cmd.h"
#include "env.h"
#include "data.h"
#include "def.h"

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

static size_t	buildhdoc(t_cmdvec *cmd, t_token *tokens, size_t i)
{
	t_vector	arg;
	t_redir		redir;

	v_init(&arg, sizeof(char), 16);
	redir.type = thdoc;
	redir.fd = 0;
	while (tokens[i].type & (tws))
		++i;
	while (tokens[i].type && (!(tokens[i].type & (tdelim)) || tokens[i].quote))
	{
		if (tokens[i].type & (tqts | tdqts))
			redir.fd = 1;
		if (!(tokens[i].type & (tqts | tdqts)) || tokens[i].quote)
			i += v_pushstrn(&arg, tokens[i].val, tokens[i].len) * 0 + 1;
		else
			++i;
	}
	v_push(&arg, "\0");
	redir.str = (char *)arg.data;
	redir.fd = bi_heredoc(redir.str, redir.fd);
	v_push(&cmd->redirin, &redir);
	if (redir.fd == ERROR)
		return (0);
	return (i);
}

static int	buildcmd2(t_cmdvec *vec, t_token *tokens, t_cmd *cmd, size_t i)
{
	while (tokens[i].type)
	{
		if (tokens[i].type & (twrd | td | tqts | tdqts))
			i = buildwrd(vec, tokens, i);
		else if (tokens[i].type & (tdin | tdout | tapp))
			i = buildredir(vec, tokens, i + 1);
		else if (tokens[i].type & (thdoc))
			i = buildhdoc(vec, tokens, i + 1);
		else if (tokens[i].type & (tpipe))
		{
			cmd->pipecmd = malloc(sizeof(t_cmd));
			if (!cmd->pipecmd)
				exit(EXIT_FAILURE);
			if (!buildcmd(tokens + i + 1, cmd->pipecmd))
				return (freecmdvec(vec));
			break ;
		}
		else if (tokens[i].type & (tand | tor))
			break ;
		else
			++i;
		if (i == 0)
			return (0);
	}
	return (1);
}

int	buildcmd(t_token *tokens, t_cmd *cmd)
{
	int				ret;
	t_cmdvec		vec;
	const t_redir	nullredir = {0, 0, 0};

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
		return (ret);
	}
	freecmdvec(&vec);
	return (ret);
}
