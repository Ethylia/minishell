/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:38:33 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/29 13:56:20 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

int	is_ambi(const char *var)
{
	size_t		i;

	if (var)
	{
		i = -1;
		while (var[++i])
			if (is_ws(var[i]))
				return (1);
	}
	return (0);
}

static size_t	buildtdrd(t_vector *arg, t_token *token, size_t i)
{
	const char	*var;

	if (token->type & (tdelim | tdqts | tqts) || !token->type)
	{
		if ((!token->type) || ((token - 1)->quote == '\"')
			|| !(token->type & (tdqts | tqts) && token->quote != '\''))
			v_push(arg, "$");
		return (i);
	}
	var = get_varn(getdata()->local_env, token->val, token->len);
	if (!var)
		var = get_varn(getdata()->exported_env, token->val, token->len);
	if (var)
	{
		if (is_ambi(var))
		{
			write(2, "minishell: ambiguous redirect\n", 30);
			return (0);
		}
		return (v_pushstr(arg, var) * 0 + i + 1);
	}
	return (i + 1);
}

static size_t	buildredir(t_cmdvec *cmd, t_token *tokens, size_t i)
{
	t_redir			redir;
	t_vector		arg;
	t_vector *const	rv = (t_vector *)((tokens[i - 1].type == tdin)
			* (size_t)(&cmd->redirin)
			+ !(tokens[i - 1].type & tdin) * (size_t)(&cmd->redirout));

	redir.type = tokens[i - 1].type;
	while (tokens[i].type & (tws))
		++i;
	v_init(&arg, sizeof(char), 16);
	while (tokens[i].type && (!(tokens[i].type & (tdelim)) || tokens[i].quote))
	{
		if (tokens[i].type & (td))
			i = buildtdrd(&arg, tokens + i + 1, i + 1);
		else if (!(tokens[i].type & (tqts | tdqts)) || tokens[i].quote)
			i += v_pushstrn(&arg, tokens[i].val, tokens[i].len) * 0 + 1;
		else
			++i;
		if (!i)
			return (0);
	}
	v_push(&arg, "\0");
	redir.str = (char *)arg.data;
	v_push(rv, &redir);
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
		else if (tokens[i].type & (tpipe))
		{
			cmd->pipecmd = malloc(sizeof(t_cmd));
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
		return (ret);
	}
	freecmdvec(&vec);
	return (ret);
}
