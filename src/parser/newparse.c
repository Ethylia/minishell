/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:33:31 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/27 16:00:12 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/util.h"
#include "util/vector.h"
#include "cmd.h"
#include "env.h"
#include "data.h"

static void	initcmd(t_cmd *cmd)
{
	v_init(&cmd->argv, sizeof(char *), 8);
	v_init(&cmd->redirin, sizeof(t_redir), 8);
	v_init(&cmd->redirout, sizeof(t_redir), 8);
	cmd->pipecmd = NULL;
}

static size_t

static void	insertargs(t_vector *argv, const char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_ws(str[i]))
		{
			v_push(argv, &str[j]);
			while (is_ws(str[i]))
				++i;
			j = i;
		}
		else
			++i;
	}
	if (i != j)
		v_push(argv, strndupe(&str[j]));
}

static size_t	buildtd(t_vector *argv, t_token *token)
{
	const char	*arg;
	size_t		i[2];

	if (token->type & (tdelim | tdqts | tqts) || !token->type)
	{
		if (token->type & (tdqts | tqts) && !token->quote)
			++token;
	}
	arg = get_varn(getdata()->local_env, token->val, token->len);
	if (!arg)
		arg = get_varn(getdata()->exported_env, token->val, token->len);
	if (arg)
	{
		insertargs(argv, arg);
		return (1);
	}
	else
		v_push(argv, strndupe(token->val, token->len));
}

static size_t	buildarg(t_vector *argv, t_token *token)
{
	char	*arg;
	size_t	i;

	if (token->type & (td) && token->quote != '\'')
		return (buildtd(argv, token + 1));
	i = 0;
	return (i);
}

static size_t	buildwrd(t_cmd *cmd, t_token *tokens, size_t i)
{
	char	*arg;

	while (tokens[i].type & (twrd | td | tqts | tdqts))
	{
		i += buildarg(&cmd->argv, &tokens[i]);
	}
	return (i);
}

int	buildcmd(t_token *tokens, t_cmd *cmd)
{
	size_t	i;

	initcmd(cmd);
	i = 0;
	while (tokens[i].type)
	{
		if (tokens[i].type & (twrd | td | tqts | tdqts))
			i += buildwrd(&cmd, tokens, i);
		else if (tokens[i].type & (tdin | tdout | tapp))
			i += buildredir(&cmd, tokens, i);
		else if (tokens[i].type & (tpipe))
		{
			cmd->pipecmd = malloc(sizeof(t_cmd));
			if (!buildcmd(tokens + i + 1, cmd->pipecmd))
				return (0);
			break ;
		}
		else if (tokens[i].type & (tand | tor))
			break ;
		else
			++i;
	}
	return (1);
}
