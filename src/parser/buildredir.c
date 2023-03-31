/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:55:02 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/31 10:11:18 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "wildcard.h"
#include "util/vector.h"
#include "util/util.h"
#include "data.h"
#include "env.h"

static int	wis_ambi(const char **var)
{
	if (var[0] && var[1])
		return (1);
	return (0);
}

static int	is_ambi(const char *var)
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

size_t	buildredir2(t_token *tokens, size_t i, t_redir *redir)
{
	t_vector		arg;

	redir->type = tokens[i - 1].type;
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
	redir->str = (char *)arg.data;
	return (i);
}

size_t	buildredir(t_cmdvec *cmd, t_token *tokens, size_t i)
{
	t_redir			redir;
	char			**wilds;
	t_vector *const	rv = (t_vector *)((tokens[i - 1].type == tdin)
			* (size_t)(&cmd->redirin)
			+ !(tokens[i - 1].type & tdin) * (size_t)(&cmd->redirout));

	i = buildredir2(tokens, i, &redir);
	if (!i)
		return (0);
	wilds = wildcard_values(redir.str);
	if (wilds[0])
	{
		free(redir.str);
		if (wis_ambi((const char **)wilds))
		{
			write(2, "minishell: ambiguous redirect\n", 30);
			free_wildcard_values(wilds);
			return (0);
		}
		redir.str = strdupe(wilds[0]);
	}
	free_wildcard_values(wilds);
	v_push(rv, &redir);
	return (i);
}
