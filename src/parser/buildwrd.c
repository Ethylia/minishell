/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildwrd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:55:11 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/28 17:10:35 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/util.h"
#include "util/vector.h"
#include "env.h"
#include "data.h"
#include "cmd.h"

static size_t	insertargs(t_vector *argv, t_vector *arg, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (is_ws(str[i]))
		{
			v_push(arg, "\0");
			v_push(argv, &arg->data);
			v_init(arg, sizeof(char), 16);
			while (is_ws(str[i]))
				++i;
		}
		else
			v_push(arg, str + i++);
	}
	return (i);
}

static size_t	buildtd(t_vector *argv, t_vector *arg, t_token *token)
{
	const char	*var;

	if (token->type & (tdelim | tdqts | tqts) || !token->type)
	{
		if ((!token->type) || ((token - 1)->quote == '\"')
			|| !(token->type & (tdqts | tqts) && token->quote != '\''))
			v_push(arg, "$");
		return (0);
	}
	var = get_varn(getdata()->local_env, token->val, token->len);
	if (!var)
		var = get_varn(getdata()->exported_env, token->val, token->len);
	if (var && token->quote != '"')
		return (insertargs(argv, arg, var) * 0 + 2);
	else if (var)
		return (v_pushstr(arg, var) * 0 + 2);
	return (1);
}

static size_t	buildarg(t_vector *argv, t_vector *arg, t_token *token)
{
	size_t	i;

	i = 0;
	if (token->type & (td) && token->quote != '\'')
		return ((buildtd(argv, arg, token + 1)) + 1);
	else if (token->type & (tdqts | tqts) && !token->quote)
		return (1);
	else
		while (i < token->len)
			v_push(arg, token->val + i++);
	return (1);
}

size_t	buildwrd(t_cmdvec *cmd, t_token *tokens, size_t i)
{
	t_vector	arg;

	v_init(&arg, sizeof(char), 16);
	while (tokens[i].type
		&& (tokens[i].type & (twrd | td | tqts | tdqts) || tokens[i].quote))
		i += buildarg(&cmd->argv, &arg, &tokens[i]);
	if (arg.size)
	{
		v_push(&arg, "\0");
		v_push(&cmd->argv, &arg.data);
	}
	else
		free(arg.data);
	return (i);
}
